const std = @import("std");

const n: u32 = 130;//10;
var map: [n][n]u8 = undefined;

pub fn main() !void {
	const out = std.io.getStdOut().writer();
    try readInput();

    var no_distinct_visited_positions: u32 = 1; // 1 = Starting pos
    while (getGuardsPos()) |pos| {
		const x: usize, const y: usize = pos;
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
            '.' => {
                no_distinct_visited_positions += 1;
                map[fy][fx] = fd;
                // Fallthrough would be nice here
            },
            'X' => map[fy][fx] = fd,
            '#' => map[y][x] = turn,
            else => unreachable,
        }
    }

    try out.print("{d}\n", .{no_distinct_visited_positions});
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
