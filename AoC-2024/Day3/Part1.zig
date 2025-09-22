const std = @import("std");

pub fn main() !void {
	const allocator = std.heap.page_allocator;
	const stdout = std.io.getStdOut().writer();
	
	var file = try std.fs.cwd().openFile("input", .{});
	defer file.close();
	
	const program = try file.reader().readAllAlloc(allocator, std.math.maxInt(usize));
	defer allocator.free(program);
	
	var i: usize = 0;
	var result: u32 = 0;
	while (i < program.len) {
		if (program[i] != 'm') {
			i += 1;
			continue;
		}
		i += 1;
		if (!std.mem.eql(u8, program[i..i+3], "ul(")) {
			continue;
		}
		i += 3;
		var X: u32 = 0;
		for (0..3) |_| {
			if (!('0' <= program[i] and program[i] <= '9')) {
				break;
			}
			X *= 10;
			X += program[i]-'0';
			i += 1;
		}
		// 0, as arg, not present in input
		if (X == 0) continue;
		if (program[i] != ',') continue;
		i += 1;
		var Y: u32 = 0;
		for (0..3) |_| {
			if (!('0' <= program[i] and program[i] <= '9')) {
				break;
			}
			Y *= 10;
			Y += program[i]-'0';
			i += 1;
		}
		if (Y == 0) continue;
		if (program[i] != ')') continue;
		i += 1;
		result += X * Y;
	}
	try stdout.print("{d}", .{result});
}