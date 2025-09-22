const std = @import("std");

pub fn main() !void {
	const stdout = std.io.getStdOut().writer();
	
	const padding: usize = 3;
	const n = 140; // 10
	const sz = n+2*padding;
	var input: [sz][sz]u8 = [_][sz]u8{[_]u8{0}**(sz)}**sz;
	
	const file = try std.fs.cwd().openFile("input", .{});
	defer file.close();
	
	
	var buf: [512]u8 = undefined;
	
	{
		var i: usize = 0;
		while (i < n) : (i += 1) {
			const line = try file.reader().readUntilDelimiterOrEof(&buf, '\n') orelse unreachable;
			@memcpy(input[padding + i][padding..padding+n], line[0..n]);
		}
	}
	
	var no_xmas_appearances: u32 = 0;
	for (padding..n+padding) |i| {
		for (padding..n+padding) |j| {
			const isMAS = struct { fn isMAS(word: [3]u8) bool {
				return std.mem.eql(u8, &word, "MAS") or std.mem.eql(u8, &word, "SAM");
			}}.isMAS;
			const diagonal: [3]u8 = [_]u8{input[i][j], input[i+1][j+1], input[i+2][j+2]};
			const diagonal_dl: [3]u8 = [_]u8{input[i][j+2], input[i+1][j+1], input[i+2][j]};
			no_xmas_appearances += @intFromBool(isMAS(diagonal) and isMAS(diagonal_dl));
		}
	}
	try stdout.print("{d}", .{no_xmas_appearances});
}