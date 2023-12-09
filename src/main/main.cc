/**
 * Simple Combinatorial Differential Evolution (SC-DE)
 * 
 * A simple Addaptation Differential Evolution by Storn and Price.
 *
 */
#include <iostream>
#include <string>

#include "glog/logging.h"
#include "glog/stl_logging.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"

#include "src/differential_evolution/de.h"
#include "src/lib/randomlib/randomlib.h"

ABSL_FLAG(bool, verbose, false,
          "Include 'advanced' options in the menu listing");
ABSL_FLAG(std::string, message, "Hello world!", "Message to print");
ABSL_FLAG(uint32_t, year, 2020, "Current year");

ABSL_FLAG(std::vector<std::string>, names,
          std::vector<std::string>({"jack", "jim", "jamal"}),
          "comma-separated list of names the program accepts");

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true; // Log both to log file and stderr

  // LOG(INFO) << "ABC, it's easy as " << 10;
  // LOG(WARNING) << "This is a warning message";
  // LOG(ERROR) << "This is an error message";
  // LOG(FATAL) << "This is a fatal message";
  // CHECK(5 == 4) << "Check failed!";

  // absl::SetProgramUsageMessage("--massage: custom message");
  absl::ParseCommandLine(argc, argv);
  if (absl::GetFlag(FLAGS_verbose)) {
    std::cout << "Verbose "
              << ": ";
  }
  std::cout << absl::GetFlag(FLAGS_message) << std::endl;

  std::cout << absl::GetFlag(FLAGS_year) << std::endl;

  Settings settings;
  DE differential = DE(settings);

  rng_define_default_range(1, 32);
  return 0;
}