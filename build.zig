const std = @import("std");

pub fn build(b: *std.Build) void {
    const flags = [_][]const u8{
        "-Wall",
        "-Wextra",
        "-Werror=return-type",
    };
    const cflags = flags ++ [_][]const u8{
        "-std=c99",
    };

    const cxxflags = cflags ++ [_][]const u8{
        "-std=c++2b", "-fno-exceptions",
    };

    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "evok-runner",
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{
        .file = std.build.LazyPath.relative("src/main.cpp"),
        .flags = &cxxflags,
    });
    exe.linkLibC();
    exe.linkLibCpp();

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const step = b.step("run", "Runs the executable");
    step.dependOn(&run_cmd.step);
}
