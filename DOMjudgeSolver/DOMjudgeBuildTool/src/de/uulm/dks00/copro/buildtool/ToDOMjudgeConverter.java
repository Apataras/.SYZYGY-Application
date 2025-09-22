package de.uulm.dks00.copro.buildtool;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.io.UncheckedIOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.ServiceLoader;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.spi.ToolProvider;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public final class ToDOMjudgeConverter {
	private ToDOMjudgeConverter() {
	}
	private static final List<String> allProblems = List.of("stockbroker", "bestrelayteam");

	public static void main(String[] args) {
		if (args.length < 1) {
			System.err.println("Usage: toDOMjudge OPTIONS... PROBLEM");
			System.exit(1); // return;
		}

		Path src = null;
		Path dest = null;
		String problemId = null;
		/* parseArgs: */ {
			for (int i = 0; i < args.length - 1; i++) {
				switch (args[i]) {
				case "--source-path":
					src = Path.of(args[i + 1]);
					i++;
					break;
				case "--destination":
					dest = Path.of(args[i + 1]);
					i++;
					break;
				}
			}
			problemId = args[args.length - 1];
		}

		if (src == null) {
			System.err.println("--source-path DIR is missing");
			return;
		}
		if (dest == null) {
			System.err.println("--destination FILE is missing");
			return;
		}

		try {
			final String MODULE = "de.uulm.dks00.copro";
			String mainClass = "de.uulm.dks00.copro." + problemId + ".main.Main";
			List<Path> srcFiles;
			{
				final Path problemsSubDir = Path.of("de", "uulm", "dks00", "copro");
				var rootDirStream = Files.list(src.resolve(problemsSubDir)).filter(f -> !Objects.toString(f.getFileName()).equals("Main.java"));
				Path problemDir = src.resolve(problemsSubDir).resolve(Path.of(problemId));
				var problemDirStream = Files.walk(problemDir);
				srcFiles = Stream.concat(rootDirStream, problemDirStream).filter(Files::isRegularFile).collect(Collectors.toList());
			}
			SquashJob job = new SquashJob(MODULE, mainClass, src, srcFiles, dest);
			squashEverything(problemId, job);
		} catch (IOException e) {
			System.err.println("IOError");
			e.printStackTrace();
			System.exit(1); // return;
		}
	}

	record SquashJob(String module, String mainClass, Path src, List<Path> srcFiles, Path destFile) {
	}

	private static void squashEverything(String problem, SquashJob job) throws IOException {
		Files.createDirectories(job.destFile().getParent());
		try (var writer = Files.newBufferedWriter(job.destFile())) {
			Map<String, byte[]> classes = new HashMap<>();
			var tmpDir = Files.createTempDirectory(null);
			
			final class CompilerHelper {
				
				private static final ToolProvider javac;
				static {
					javac = ToolProvider.findFirst("javac").orElseThrow(RuntimeException::new);
				}
				private static final PrintStream NULL_STREAM = new PrintStream(OutputStream.nullOutputStream());
				public static void compile(Path src, Path srcFile, Path dest) {
					int result = javac.run(System.out, System.err, "--release", "10", "-implicit:none", "--source-path",
							src.toAbsolutePath().toString(), "-d", dest.toAbsolutePath().toString(),
							srcFile.toAbsolutePath().toString());
					if (result != 0) {
						System.err.println("RRRR");
						System.exit(2); // return;
					}
				}
			}
			StringBuilder srcCode = new StringBuilder();
			for (var srcFile : job.srcFiles()) {
				srcCode
					.append(job.src().relativize(srcFile))
					.append(System.lineSeparator())
					.append(Files.readString(srcFile).replace("*/", ""))
					.append(System.lineSeparator());
				// Compile srcFiles
				CompilerHelper.compile(job.src(), srcFile, tmpDir);

				// Store compiled files (.class files) in classes Map
				record ClassInfo(String name, byte[] b) {
				}
				var tmpClasses = Files.walk(tmpDir).filter(Files::isRegularFile).map(f -> {
					byte[] b;
					try {
						b = Files.readAllBytes(f);
					} catch (IOException e) {
						throw new UncheckedIOException(e);
					}
					Path tmp = tmpDir.resolve(f);
					Path internalPath = tmpDir.resolve(f).subpath(2, tmp.getNameCount());
					String className = internalPath.toString().replace(".class", "").replace(File.separatorChar, '.');
					return new ClassInfo(className, b);
				}).collect(Collectors.toMap(ClassInfo::name, ClassInfo::b));
				classes.putAll(tmpClasses);
			}

			Predicate<String> isUnimportantModuleDirective = new Predicate<String>() {
			
				private boolean withIgnore = false;
				
				@Override
				public boolean test(String l) {
					String ll = l.toLowerCase();
					/*l = l.toLowerCase();
					if (withIgnore) {
						if (l.contains(";"))
							withIgnore = false;
						return true;
					}

					final String ll = l;
					if (l.contains("with")) {
						if (!l.contains(problem.toLowerCase())
								&& allProblems.stream().anyMatch(s->ll.contains(s))) {
							withIgnore = true;
							return true;
						}
						return false;
					}*/
					return !ll.contains(problem)
							&& allProblems.stream().anyMatch(s->ll.contains(s));
				}
			};
			srcCode
				.append("module-info.java")
				.append(System.lineSeparator())
				.append(Files.readString(job.src().resolve("module-info.java"))
					.lines().filter(isUnimportantModuleDirective.negate())
					.collect(Collectors.joining(System.lineSeparator())))
				.append(System.lineSeparator());
			CompilerHelper.compile(job.src(), job.src().resolve("module-info.java"), tmpDir);
			byte[] modBytes = Files.readAllBytes(tmpDir.resolve("module-info.class"));
			Function<byte[], String> codePacker = b -> {
				var sb = new StringBuilder();
				for (int i = 0; i < b.length; i+=2) {
					char c = i == b.length-1 ? (char)(b[i]&0xFF) : (char) (((b[i]&0xFF) << 8) | (b[i+1]&0xFF));
					if (c == '+')
						sb.append('+')
						.append('0');
					else if (c == '\"')
						sb.append('+')
						.append('1');
					else if (c == '\r')
						sb.append('+')
						.append('2');
					else if (c == '\n')
						sb.append('+')
						.append('3');
					else if (c == '\\')
						sb.append('+')
						.append('4');
					else sb.append(c);
				}
				return b.length + "+" +sb.toString();
			};
			String modBytesStr = codePacker.apply(modBytes);//Arrays.toString(modBytes).transform(s -> s.substring(1, s.length()-1)).replace(" ", "");
			/*Function<Map.Entry<String, byte[]>, String> stringifier = e -> {
				return "\t\t\tentry(\"%s\", new byte[] { %s })"
					.formatted(e.getKey(), 
							Arrays.toString(e.getValue()).transform(s -> s.substring(1, s.length()-1)).replace(" ", ""));
			};*/
			
			Function<Map.Entry<String, byte[]>, String> stringifier = 
					e -> {
				String r = "\t\t\tentry(\"%s\", unpackCode(\"%s\"))".formatted(e.getKey(), codePacker.apply(e.getValue()));
				return r;
			};
			String entryArgs = classes.entrySet().stream()
					.map(stringifier)
					.collect(Collectors.joining(",\n"));
			writer.write(
					"""
							// Built by THE building tool
							// I wanted to write my solution using the modular service-provider mechanism
							// and dont have everything in a single source file.
							// In order to achieve that I have to precompile my classes and load them at runtime.
							// This generated class basically loads precompiled binaries packed into the source code (as strings).
							//! Source code is at the bottom.

							import java.io.ByteArrayInputStream;
							import java.io.IOException;
							import java.lang.module.Configuration;
							import java.lang.module.ModuleDescriptor;
							import java.lang.module.ModuleFinder;
							import java.lang.module.ModuleReader;
							import java.lang.module.ModuleReference;
							import java.lang.reflect.Method;
							import java.net.URI;
							import java.util.Map;
							import java.util.Optional;
							import java.util.Set;
							import java.util.stream.Stream;
							import static java.util.Map.entry;

							public final class Solution {
								private Solution() {}

								public static void main(String[] args) throws Throwable {
									final Map<String, byte[]> classes = Map.ofEntries(
							%CLASSES%
									);
									// Create module and layer from classfile structure
									byte[] modBytes = unpackCode(\"%MODULE_BYTES%\");
									ModuleDescriptor modDescr = ModuleDescriptor.read(new ByteArrayInputStream(modBytes));
									ModuleReference modRef = new InaccessibleModuleReference(modDescr);
									ModuleFinder moduleFinder = new SingleInMemoryModuleFinder(modRef);
									ModuleLayer curModLayer = ModuleLayer.boot();
									Configuration newConfig = curModLayer.configuration().resolve(moduleFinder, ModuleFinder.of(), Set.of("%MODULE%"));
									ClassLoader modCl = new InMemoryClassLoader(classes);
									ModuleLayer newModLayer = curModLayer.defineModules(newConfig, __ -> modCl);

									// "Load" module and execute selected main class
									ClassLoader cl = newModLayer.findLoader("%MODULE%");
									// Load all providers
									for (var mod : newConfig.modules()) {
										for (var provides : mod.reference().descriptor().provides()) {
											for (var provider : provides.providers()) {
												if (provider.toLowerCase().contains(\"%PROBLEM%\"))
													cl.loadClass(provider);
											}
										}
									}
									// Find Main class and execute main
									Class<?> mainClass = cl.loadClass("%MAIN_CLASS%");
									ClassLoader ccl = Thread.currentThread().getContextClassLoader();
									Thread.currentThread().setContextClassLoader(cl);
									Method mainMethod = mainClass.getMethod("main", String[].class);
									mainMethod.invoke(null, (Object)args);
									Thread.currentThread().setContextClassLoader(ccl);
								}
								private static byte[] unpackCode(String s) {
									int i = 0;
									int len = 0;
									while (i < s.length()) {
										if (s.charAt(i) == '+')
											break;
										len *= 10;
										len += s.charAt(i) - '0';
										i++;
									}
									byte[] b = new byte[len];
									int j = 0;
									for (i++; i < s.length(); i++) {
										if (s.charAt(i) != '+') {
											if (j < len-1)
												b[j++] = (byte)(s.charAt(i) >> 8);
											b[j++] = (byte)(s.charAt(i) & 0xFF);
										} else {
											char c;
											switch (s.charAt(++i)) {
												case '0': c = '+'; break;
												case '1': c = '\\"'; break;
												case '2': c = '\\r'; break;
												case '3': c = '\\n'; break;
												case '4': c = '\\\\'; break;
												default : throw new AssertionError();
											};
											if (j < len-1)
												b[j++] = (byte)(c >> 8);
											b[j++] = (byte)(c & 0xFF);
										}
									}
									return b;
								}
								private static final class InMemoryClassLoader extends ClassLoader {

									private final Map<String, byte[]> classes;

									public InMemoryClassLoader(Map<String, byte[]> classes) { this(classes, null); }
									public InMemoryClassLoader(Map<String, byte[]> classes, ClassLoader parent) {
										super(parent);
										this.classes = classes;
									}

									@Override protected Class<?> findClass(String name) throws ClassNotFoundException {
										byte[] b = classes.get(name);
										if (b == null)
											throw new ClassNotFoundException();
										return defineClass(name, b, 0, b.length);
									}
								}
								private static final class InaccessibleModuleReference extends ModuleReference {

									public InaccessibleModuleReference(ModuleDescriptor descriptor) {
										super(descriptor, null);
									}

									@Override public ModuleReader open() {
										return new ModuleReader() {

											private volatile boolean closed;

											private void ensureOpen() throws IOException {
												if (closed)
													throw new IOException("Stream closed");
											}
											@Override public Optional<URI> find(String name) throws IOException {
												ensureOpen();
												return Optional.empty();
											}
											@Override public Stream<String> list() throws IOException {
												ensureOpen();
												return Stream.empty();
											}
											@Override public void close() {
												closed = true;
											}
										};
									}
								}
								private static final class SingleInMemoryModuleFinder implements ModuleFinder {

									private final ModuleReference ref;

									public SingleInMemoryModuleFinder(ModuleReference reference) {
										this.ref = reference;
									}

									@Override public Optional<ModuleReference> find(String name) {
										return ref.descriptor().name().equals(name)
											? Optional.of(ref) : Optional.empty();
									}
									@Override public Set<ModuleReference> findAll() {
										return Set.of(ref);
									}
								}
							}
							
							//--------------------------------------
							// Source code starts here
							//--------------------------------------
							/*
							%SOURCE_CODE%
							*/
							"""
							.replace("%CLASSES%", entryArgs).replace("%MODULE_BYTES%", modBytesStr)
							.replace("%MODULE%", job.module()).replace("%MAIN_CLASS%", job.mainClass())
							.replace("%PROBLEM%", problem.toLowerCase())
							.replace("%SOURCE_CODE%", srcCode.toString().stripTrailing()));
		}
	}
}
