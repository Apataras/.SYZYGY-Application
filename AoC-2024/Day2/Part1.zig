const std = @import("std");

pub fn main() !void {
	const allocator = std.heap.page_allocator;
    const stdout = std.io.getStdOut().writer();
	
	const file = try std.fs.cwd().openFile("input", .{});
	var reader = file.reader();
    var line_buffer: [256]u8 = undefined; // Adjust size as needed
	var reports: std.ArrayList(std.ArrayList(u32)) = std.ArrayList(std.ArrayList(u32)).init(allocator);
    while (try reader.readUntilDelimiterOrEof(&line_buffer, '\n')) |line| {
		var report = std.ArrayList(u32).init(allocator);
		var tokenizer = std.mem.tokenizeAny(u8, line, " ");
		while (tokenizer.next()) |number_str| {
			const number = try std.fmt.parseInt(u32, number_str, 10);
			try report.append(number);
		}
		try reports.append(report);
	}
	var no_safe_reports: u32 = 0;
	for (reports.items) |report| {
		const is_inc = report.items[0] < report.items[1];
		const is_dec = report.items[0] > report.items[1];
		var is_safe = is_inc != is_dec;
		for (0..report.items.len-1) |i| {
			if (is_inc) {
				is_safe = is_safe and report.items[i] < report.items[i+1];
			}
			if (is_dec) {
				is_safe = is_safe and report.items[i] > report.items[i+1];
			}
			const adj_level_diff: u32 = @intCast(@abs(@as(i64,report.items[i]) - @as(i64,report.items[i+1])));
			is_safe = is_safe and (1 <= adj_level_diff and adj_level_diff <= 3);
		}
		if (is_safe) {
			no_safe_reports += 1;
		}
	}
	try stdout.print("{d}\n", .{no_safe_reports});
}