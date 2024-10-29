#ifndef INCLUDE_LIB_CONTROL_H_
#define INCLUDE_LIB_CONTROL_H_

#include <functional>
#include <initializer_list>
#include <map>
#include <optional>
#include <string>

#include "io.h"

namespace ctoast {
class Context {
 public:
  [[nodiscard]] bool shouldExit() const;
  void Exit();

  Context();
  ~Context() = default;

 private:
  bool shouldExit_;
};

void Loop(const std::function<void(Context &)> &body);

void PrintAuthor();
void PrintDescription(const std::string &description);
void PrintTask(const std::string &task_name,
               std::optional<std::string> task_option);

void PrintGreeting();

using UsageOption = char;
CinResult<UsageOption> GetUsage();

void PrintError(const std::string &error);

struct Usage {
  char Option;
  std::string Descritption;
  std::function<CinResult<void>(Context &)> Function;

  static Usage CreateQuit();

  Usage(char option, std::string desc,
        std::function<CinResult<void>(Context &)> func);
};

class UsageData {
 public:
  struct Builder {
    std::map<char, Usage> Accumulator;
    Builder &Push(Usage usage);
    UsageData Build();
  };

  void operator()(Context &ctx);

  UsageData(std::map<char, Usage> usages);
  ~UsageData() = default;

 private:
  std::map<char, Usage> usages_;
};

std::function<void(Context &)> CreateUsages(
    const std::initializer_list<Usage> &list);

struct ProgramInfo {
  std::string Description;
  std::string TaskName;
  std::optional<std::string> TaskOption;

  std::initializer_list<Usage> Usages;
};

void PrintMenu(const ProgramInfo &info);
}  // namespace ctoast

#endif  // INCLUDE_LIB_CONTROL_H_
