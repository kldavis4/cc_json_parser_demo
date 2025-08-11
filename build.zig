const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "json-parser",
        .target = target,
        .optimize = optimize,
    });

    exe.addCSourceFile(.{ .file = b.path("src/json_parser.c") });
    exe.addCSourceFile(.{ .file = b.path("src/cJSON.c") });
    exe.linkLibC();

    const install_artifact = b.addInstallArtifact(exe, .{
        .dest_dir = .{ .override = .{ .custom = "../bin" } },
    });
    b.getInstallStep().dependOn(&install_artifact.step);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the JSON parser program");
    run_step.dependOn(&run_cmd.step);
}