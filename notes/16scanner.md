1.
print "${drink} will be ready in ${steep + cool} minutes.";

-- option 1, no change in lexing, offload to the parser/evaluator (parse expressions grammar)
TOKEN_STRING "${drink} will be ready in ${steep + cool} minutes."

+ Makes the lexer simpler, offloading to downstream components.

-- option2, preprocessor
print string(drink) + " will be ready in " + string(steep + cool) + " minutes."
 
+ Makes the lexer simpler, at no cost to the complexity of future components.
+ Care needed to implement efficiently, or at least to process down to a efficient representation.

-- option3, lexer modes
There's a separate language that's defined between double quotes. Switch to another lexing mode
when lexing within the string. Store information about whether or not we're inside an interpolation context.

TOKEN_IDENTIFIER drink
TOKEN_STRING " will be ready in "
TOKEN_IDENTIFIER steep
TOKEN_ADD
TOKEN_IDENTIFIER cool
TOKEN_STRING minutes.

Example: Swift Interpolation https://github.com/apple/swift/blob/main/lib/Parse/Lexer.cpp#L1834