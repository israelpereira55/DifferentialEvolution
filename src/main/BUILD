load("@rules_cc//cc:defs.bzl", "cc_binary")

# Demo of genrul
genrule(
    name = "test",
    srcs = [],
    outs = ["test.txt"],
    cmd = "echo 'Hello world' > $@",
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
            "@com_google_absl//absl/flags:flag",
            "@com_google_absl//absl/flags:parse",
            "@com_google_absl//absl/flags:usage",
            "@glog",
            "//src/differential_evolution:DE",
            "//src/lib/randomlib:RandomLib",
            ],
)