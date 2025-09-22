const std = @import("std");

pub fn main() !void {
	const allocator = std.heap.page_allocator;
	const stdout = std.io.getStdOut().writer();
	const file = try std.fs.cwd().openFile("input", .{});
	defer file.close();
	
	const n = 192; // no updates
	const m = 1176; // no ordering rules
	var updates: [n]std.ArrayList(u32) = undefined;
	var ordering_rules: [m][2]u32 = undefined;
	var buf: [512]u8 = undefined;
	for (0..m) |i| {
		const line = try file.reader().readUntilDelimiterOrEof(&buf, '\n') orelse unreachable;
		var parts = std.mem.splitSequence(u8, line, "|");
		ordering_rules[i][0] = try std.fmt.parseInt(u32, parts.next().?, 10);
		ordering_rules[i][1] = try std.fmt.parseInt(u32, parts.next().?, 10);
	}
	{
		_ = try file.reader().readUntilDelimiterOrEof(&buf, '\n') orelse unreachable; // Empty line
	}
	for (0..n) |i| {
		const line = try file.reader().readUntilDelimiterOrEof(&buf, '\n') orelse unreachable;
		var parts = std.mem.splitSequence(u8, line, ",");
		updates[i] = std.ArrayList(u32).init(allocator);
		while (parts.next()) |part| {
			try updates[i].append(try std.fmt.parseInt(u32, part, 10));
		}
	}	
	defer {
		for (updates) |update| {
			update.deinit();
		}
	}
	
	var sum_of_middles: u32 = 0;
	var ops: u64 = 0;
	for (updates) |update| {
		if (isCorrectlyOrdered(update, &ordering_rules)) continue;
		for (0..update.items.len-1) |i| {
			for (i+1..update.items.len) |j| {
				for (ordering_rules) |ordering_rule| {
					ops += 1;
					if (update.items[i] == ordering_rule[1]
						and update.items[j] == ordering_rule[0]) {
						const tmp = update.items[i];
						update.items[i] = update.items[j];
						update.items[j] = tmp;
					}
				}
			}
		}
		sum_of_middles += update.items[update.items.len / 2];
	}
	try stdout.print("{d}\n", .{sum_of_middles});
	try stdout.print("{d}\n", .{ops});
}
fn isCorrectlyOrdered(update: std.ArrayList(u32), ordering_rules: [][2]u32) bool {
	var is_correctly_ordered = true;
	i_l: for (0..update.items.len) |i| {
		j_l: for (i+1..update.items.len) |j| {
			for (ordering_rules) |ordering_rule| {
				if (update.items[i] == ordering_rule[0] and update.items[j] == ordering_rule[1]) {
					continue :j_l;
				}
			}
			is_correctly_ordered = false;
			break :i_l;
		}
	}
	return is_correctly_ordered;
}