#include "ctoast/control.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <variant>

#include "ctoast/io.h"

namespace ctoast {
bool Context::shouldExit() const {
  return this->shouldExit_;
}

void Context::Exit() {
  this->shouldExit_ = true;
}

Context::Context() {
  shouldExit_ = false;
}

void Loop(const std::function<void(Context &)> &body) {
  Context ctx = Context();
  while (!ctx.shouldExit()) {
    body(ctx);
  }
}

void PrintAuthor() {
  std::cout << "Выполнил Забережный Тимофей Алексеевич, гр. 453501\n";
}

void PrintDescription(const std::string &description) {
  std::cout << description << '\n';
}

void PrintTask(const std::string &task_name,
               std::optional<std::string> task_option) {
  std::cout << "Задание " << task_name;
  if (task_option.has_value()) {
    std::cout << ", вариант " << task_option.value();
  }

  std::cout << '\n';
}

void PrintGreeting() {
  std::cout << "Для опций введите h\n";
}

CinResult<UsageOption> GetUsage() {
  std::cout << "~>";
  return Read<char>("Ожидался символ");
}

void PrintError(const std::string &error) {
  std::cout << "Ошибка: " << error << ".\n";
}

Usage::Usage(char option, std::string desc,
             std::function<void(Context &)> func) {
  Option = option;
  Descritption = std::move(desc);
  Function = std::move(func);
}

UsageData::UsageData(std::map<char, Usage> usages) {
  usages_ = std::move(usages);
}

UsageData::Builder &UsageData::Builder::Push(Usage usage) {
  Accumulator.emplace(usage.Option, usage);
  return *this;
}

UsageData UsageData::Builder::Build() {
  return UsageData(Accumulator);
}

void UsageData::operator()(Context &ctx) {
  std::cout << "~> ";
  CinResult<char> option = Read<char>("Ожидался символ");

  if (std::holds_alternative<std::string>(option)) {
    PrintError(std::get<std::string>(option));
    return;
  }

  char symbol = std::get<char>(option);
  if (usages_.count(symbol) == 0) {
    std::string error_head("Неизвестная опция - ");
    PrintError(error_head.append(1, symbol));
    return;
  }

  const Usage &usage = usages_.at(symbol);
  usage.Function(ctx);
}

std::function<void(Context &)> CreateUsages(
    const std::initializer_list<Usage> &list) {
  UsageData::Builder b = UsageData::Builder();

  for (const auto &item : list) {
    b.Push(item);
  }
  std::string str = "";
  std::for_each(list.begin(), list.end(), [&str = str](const Usage &u) {
    str.append(1, u.Option);
    str += " - ";
    str += u.Descritption;
    str.append(1, '\n');
  });
  b.Push(Usage('h', "Справка", [str](Context &_) -> void {
    std::cout << str << "h - Эта справка\n";
  }));

  return b.Build();
}

void PrintMenu(const ProgramInfo &info) {
  PrintTask(info.TaskName, info.TaskOption);
  PrintDescription(info.Description);
  PrintAuthor();
  PrintGreeting();

  Loop(CreateUsages(info.Usages));
}
}  // namespace ctoast
