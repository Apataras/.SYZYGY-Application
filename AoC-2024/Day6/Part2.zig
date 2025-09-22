const std = @import("std");

const n: u32 = 130;//10;
var map: [n][n]u8 = undefined;

pub fn main() !void {
	const out = std.io.getStdOut().writer();
	const allocator = std.heap.page_allocator;
    try readInput();

    var no_loops: u32 = 0;
	const og_map = map;
	for (0..n) |uy| {
		for (0..n) |ux| {
			//std.debug.print("{d}-{d}\n",.{ux,uy});
			map[uy][ux] = 'O';
			
			var set = std.AutoHashMap(struct{usize,usize,u8},bool).init(allocator);
			var has_loop = false;
			while (getGuardsPos()) |pos| {
				const x: usize, const y: usize = pos;
				
				if (set.get(.{x,y,map[y][x]})) |_| {
					has_loop = true;
					break; 
				}
				try set.put(.{x,y,map[y][x]}, true);
			
				const fx: usize, const fy: usize, const fd: u8, const turn: u8 = switch (map[y][x]) {
					'^' => .{x,y-%1,'^', '>'},
					'>' => .{x+1,y,'>', 'v'},
					'v' => .{x,y+1,'v', '<'},
					'<' => .{x-%1,y,'<', '^'},
					else => unreachable,
				};
				
				map[y][x] = 'X';
				if (!(0 <= @as(isize,@bitCast(fx)) and fx < n and 0 <= @as(isize,@bitCast(fy)) and fy < n)) continue;
				switch (map[fy][fx]) {
					'.', 'X' => map[fy][fx] = fd,
					'#', 'O' => map[y][x] = turn,
					else => unreachable,
				}
			}
			if (has_loop)
				no_loops += 1;
			map = og_map;
		}
	}

    try out.print("{d}\n", .{no_loops});
}

fn readInput() !void {
    const file = try std.fs.cwd().openFile("input", .{});
    defer file.close();

    var buf: [n + 1]u8 = undefined;
    for (0..n) |y| {
        _ = try file.reader().read(&buf);
        @memcpy(&map[y], buf[0..n]);
    }
}

fn getGuardsPos() ?struct { usize, usize } {
    for (0..n) |y| {
        for (0..n) |x| {
            const cell = map[y][x];
            if (cell == '^' or cell == '>' or cell == 'v' or cell == '<')
                return .{ x, y };
        }
    }
    return null;
}
