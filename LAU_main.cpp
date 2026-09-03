#include "LAU_Interpretator.h"
#include "LAU_parser.h"
#include "LAU_lexer.h"
#include <iostream>
int main()
{
    std::string text = "num = 5; a = true; c = 2 + 3; text = 'hello';";
    Context context;
    try
    {
        std::unique_ptr<Lexer> lexer = std::make_unique<Lexer>(text);
        lexer->convert_to_tokens();

        std::vector<std::unique_ptr<ASTNode>> nodes;
        std::shared_ptr<BlockNode> block_node = std::make_shared<BlockNode>(std::move(nodes));

        std::vector<TokenData::Token> tokens = lexer->get_tokens();
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokens), std::move(block_node), context);
        parser->parse();

        std::unique_ptr<Interpretator> interpretator = std::make_unique<Interpretator>(std::move(block_node));
        interpretator->interpret(context);
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