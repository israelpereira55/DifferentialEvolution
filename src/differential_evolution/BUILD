load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "DE",
    srcs = [
            "de.cc",
            "individual.cc",
           ],
    hdrs = [
            "de.h",
            "individual.h",
           ],
    visibility = ["//visibility:public"],
    deps = [
            "//src/differential_evolution/settings:SettingsLib",
            "//src/lib/randomlib:RandomLib",
            "@glog",
           ],
)
