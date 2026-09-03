#include "LAU_Interpretator.h"
#include "LAU_parser.h"
#include "LAU_lexer.h"
#include <iostream>
int main()
{
    std::string text = "num = 5; a = true; c = 2 + 3;";
    std::cout << "main func started.\n";
    Context context;
    try
    {
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(text);
        lexer->convert_to_tokens();
        std::cout << "Lexer converted text.\n";

        std::vector<std::unique_ptr<ASTNode>> nodes;
        std::shared_ptr<BlockNode> block_node = std::make_shared<BlockNode>(std::move(nodes));

        std::vector<TokenData::Token> tokens = lexer->get_tokens();
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokens), std::move(block_node), context);
        parser->parse();
        std::cout << "Parser parsed tokens.\n";

        std::unique_ptr<Interpretator> interpretator = std::make_unique<Interpretator>(std::move(block_node));
        interpretator->interpret(context);
        std::cout << "Interpretation finished successfully.\n";
    }
    catch (const Error::SyntaxError &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const Error::ValueError &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const Error::NameError &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const Error::ZeroDivisionError &e)
    {
        std::cout << e.what() << '\n';
    }
    catch (...)
    {
        std::cout << "Unknown error." << std::endl;
    }
    return 0;
}