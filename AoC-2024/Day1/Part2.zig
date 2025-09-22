const std = @import("std");

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    // Open the file
	var file = try std.fs.cwd().openFile("input", .{});
    
	// Create two lists to store the integers
    var list1 = std.ArrayList(i32).init(allocator);
    defer list1.deinit();

    var list2 = std.ArrayList(i32).init(allocator);
    defer list2.deinit();

    // Read the file line by line
    var reader = file.reader();
    var line_buffer: [256]u8 = undefined; // Adjust size as needed
    while (try reader.readUntilDelimiterOrEof(&line_buffer, '\n')) |line_slice| {
        // Parse the line into two integers
        var tokenizer = std.mem.tokenizeAny(u8, line_slice, " ");
		
		const number1_str = tokenizer.next() orelse return error.InvalidFormat;
		const number2_str = tokenizer.next() orelse return error.InvalidFormat;

        const number1 = try std.fmt.parseInt(i32, number1_str, 10);
        const number2 = try std.fmt.parseInt(i32, number2_str, 10);

        // Append to the lists
        try list1.append(number1);
        try list2.append(number2);
    }

    // Print the lists for verification
    // std.debug.print("List 1: {d}\n", .{list1.items});
    // std.debug.print("List 2: {d}\n", .{list2.items});
	
	std.mem.sort(i32, list1.items, {}, comptime std.sort.asc(i32));
	std.mem.sort(i32, list2.items, {}, comptime std.sort.asc(i32));
	
	var similarityScore: u32 = 0;
	for (0..list1.items.len) |i| {
		var cnt: u32 = 0;
		for (0..list2.items.len) |j| {
			if (list2.items[j] == list1.items[i]) {
				cnt += 1;
			}
		}
		const x: u32 = @intCast(list1.items[i]);
		similarityScore += x * cnt;
	}
	std.debug.print("{d}", .{similarityScore});
}
