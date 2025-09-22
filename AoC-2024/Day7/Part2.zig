const std = @import("std");
const data = @embedFile("input");

pub fn main() !void {
	const allocator = std.heap.page_allocator;
	const out = std.io.getStdOut().writer();
	
	var eqs = std.ArrayList(Eq).init(allocator);
	var lines = std.mem.tokenizeSequence(u8, data, "\n");
    while(lines.next()) |line| {
		var ops = std.ArrayList(u64).init(allocator);
		var parts = std.mem.tokenizeSequence(u8, line, " ");
		const x = parts.next() orelse unreachable;
		const test_value = try std.fmt.parseInt(u64,x[0..x.len-1],10);
		while (parts.next()) |part| {
			try ops.append(try std.fmt.parseInt(u64,part,10));
		}
        const eq = Eq{.test_value=test_value,.operands=ops,};
		try eqs.append(eq);
    }
	
	var result: u64 = 0;
	for (eqs.items) |eq| {
		if (isPossiblyTrue(eq)) {
			result += eq.test_value;
		}
	}
	
	try out.print("{d}\n", .{result});
}

fn isPossiblyTrue(eq: Eq) bool {
	for (0..@as(u64,1)<<@intCast(eq.operands.items.len-1)) |O| {
		for (0..@as(u64,1)<<@intCast(eq.operands.items.len-1)) |NO| {
			var result: u64 = eq.operands.items[0];
			for (1..eq.operands.items.len) |i| {
				const op: u8 = if ((O & (@as(u64,1) << @intCast(i-1))) == 0) '+' else 
					if ((NO & (@as(u64,1) << @intCast(i-1))) == 0) '*' else '|';
				switch (op) {
					'+' => result += eq.operands.items[i],
					'*' => result *= eq.operands.items[i],
					'|' => {
						var sop = eq.operands.items[i];
						const sop2 = sop;
						var f: u64 = 1;
						while (sop > 0) {
							f *= 10;
							sop /= 10;
						}
						result = result * f + sop2;
					},
					else => unreachable,
				}
			}
			if (result == eq.test_value) {
				return true;
			}
		}
	}
	return false;
}

const Eq = struct {
	test_value: u64,
	operands: std.ArrayList(u64),
	
	pub fn init(test_value: u64, operands: std.ArrrayList(u64), _: std.Allocator) Eq {
		return .{
			test_value,
			operands
		};
	}
};