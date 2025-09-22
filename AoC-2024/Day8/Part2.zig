const std = @import("std");
const print = std.debug.print;

const input = @embedFile("input");
const map = xa: {
	@setEvalBranchQuota(10000);
	var it = std.mem.splitSequence(u8, input, "\n");
	var i: u32 = 1;
	const firstRow = it.next() orelse unreachable;
	const l = firstRow.len;
	var result: [l][l]u8 = [_][l]u8{[_]u8{0}**l}**l;
	const copyTo = struct {
		fn copyTo(comptime T: anytype, na: comptime_int, to: [*]T, from: [] const T) void {
			for (0..na) |ia| {
				to[ia] = from[ia];
			}
		}
	}.copyTo;
	copyTo(u8, l, &result[0], firstRow);
	while (it.next()) |row| : (i += 1) {
		if (i == l) break;
		//@compileLog(i,l);
		copyTo(u8, l, &result[i], row);
	}
	
	break :xa result;
};
const n = map.len;

pub fn main() !void {
	const allocator = std.heap.page_allocator;
	var antena_locs_map = std.AutoHashMap(u8, std.ArrayList(Loc)).init(allocator);
	for (0..n) |y| {
		for (0..n) |x| {
			switch (map[y][x]) {
				'.' => {},
				'0'...'9', 'a'...'z', 'A'...'Z' => |freq| { 
					var lista: std.ArrayList(Loc) = undefined;
					if (antena_locs_map.get(freq)) |liste| {
						lista = liste;
						print("CONTAINED {d}\n",.{liste.items.len});
					} else {
						lista = std.ArrayList(Loc).init(allocator);
					}
					try lista.append(.{.x=@intCast(x),.y=@intCast(y)}); 
					try antena_locs_map.put(freq, lista);
					
				},
				else => print("HI {}\n", .{map[y][x]}),
			}
		}
	}
	var it = antena_locs_map.iterator();
	var antinode: [n][n]bool = [_][n]bool{[_]bool{false}**n}**n;
	while (it.next()) |kv| {
		const freq = kv.key_ptr.*;
		const locs = kv.value_ptr.*;
		print("KEY FREQ {}\n", .{freq}); 
		if (locs.items.len == 0) continue;
		
		for (0..locs.items.len-1) |i| {
			for (i+1..locs.items.len) |j| {
				const an_x: isize = (locs.items[i].x-locs.items[j].x);
				const an_y: isize = (locs.items[i].y-locs.items[j].y);
				const vggt = ggT(isize, @intCast(@abs(an_x)), @intCast(@abs(an_y)));
				const r_x = @divExact(an_x,vggt);
				const r_y = @divExact(an_y,vggt);
				for (0..n/@min(@abs(r_x),@abs(r_y))) |ma| {
					for ([_]isize{-1,1}) |fac| {
						const nn_x = locs.items[i].x + fac * @as(isize,@intCast(ma)) * r_x;
						const nn_y = locs.items[i].y + fac * @as(isize,@intCast(ma)) * r_y;
						if (0 <= nn_x and nn_x < n and 0 <= nn_y and nn_y < n) 
							antinode[@intCast(nn_y)][@intCast(nn_x)] = true;
					}
				}
			}
		}
	}
	
	var no_unique_locs: u32 = 0;
	for (antinode) |row| {
		for (row) |c| {
			if (c) no_unique_locs += 1;
		}
	}
	
	print("{d}\n", .{no_unique_locs});
}
pub fn ggT(comptime T: type, a: T, b: T) T {
    if (b == 0) {
        return a;
    } else {
        return ggT(T, b, @mod(a,b));
    }
}
const Loc = struct {
	x: isize,
	y: isize,
};
