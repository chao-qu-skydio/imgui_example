#include <absl/log/log.h>
#include <fmt/core.h>

int main(int argc, char **argv) {
  LOG(INFO) << fmt::format("Hello, world!");
  LOG(WARNING) << fmt::format("Hello, world!");
}
