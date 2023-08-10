#include <iostream>
static llvm::cl::OptionCategory MatcherCategory("Matcher");

using namespace llvm;

int main(int argc, const char **argv) {
  google::InitGoogleLogging(argv[0]);

  auto ExpectedParser = CommonOptionsParser::create(argc, argv, MatcherCategory);
  if (!ExpectedParser) {
    // Fail gracefully for unsupported options.
    std::cerr << "ExpectedParser error, return" << std::endl;
    return 1;
  }

  CommonOptionsParser& op = ExpectedParser.get();
  ClangTool Tool(op.getCompilations(), op.getSourcePathList());

  Tool.run(newFrontendActionFactory<ConvertAction>().get());
}
