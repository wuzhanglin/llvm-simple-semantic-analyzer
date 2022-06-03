#include "Parser.h"
#include "SemanticAnalyzer.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::opt<std::string> input(llvm::cl::Positional, llvm::cl::desc("<input expression>"), llvm::cl::init(""));

int main(int argc, const char** argv)
{
    llvm::InitLLVM llvmInitializer(argc, argv);
    llvm::cl::ParseCommandLineOptions(argc, argv, "SimpleParser - a simple code parser\n");
    llvm::outs() << "Input: \"" << input << "\"\n";

    Lexer lexer(input);
    Parser parser(lexer);
    AST* tree = parser.Parse();
    if (!tree || parser.HasError())
    {
        llvm::errs() << "Syntax errors occured\n";
        return 1;
    }

    SemanticAnalyzer semanticAnalyzer;
    if (semanticAnalyzer.Analysis(tree))
    {
        llvm::errs() << "Semantic errors occured\n";
        return 1;
    }

    llvm::outs() << "Semantic check passed\n\n";
    return 0;
}
