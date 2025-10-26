#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Symbol;
class ASTNode {
public:
    std::string name;
    std::string lexeme = "default";
    std::string type = "default";
    std::vector<ASTNode*> children;
    ASTNode* parent;
    bool processed = false;
    int line_number = 0;  // ADD THIS LINE

    Symbol* symbol=nullptr;

    // Constructors - UPDATE to include line number
    ASTNode(const std::string &name_, const std::string &lexeme_ = "", int line = 0)
        : name(name_), lexeme(lexeme_), parent(nullptr), line_number(line) {}  // ADD line_number(line)

    // Add child nodes
    void addChild(ASTNode* child);
    void addChild(const std::string &childName, const std::string &childLexeme);
    void addChild(const std::string &childName, const std::string &childLexeme, int line);  // KEEP THIS

    // Print / debug
    void printTree(int depth = 0, std::string prefix = "");
    void generateDOT(std::ofstream &out, int &nodeId);

    // Helper to check if node has specific name
    bool isName(const std::string& n) const { return name == n; }
    
    // Helper to get child by index safely
    ASTNode* getChild(size_t index) {
        return (index < children.size()) ? children[index] : nullptr;
    }
    
    // Helper to count children
    size_t childCount() const { return children.size(); }

    // Type helpers
    void setType(const std::string &type) { this->type = type; }
    std::string getType() const { return type; }
    std::string getLexeme() const { return lexeme; }
    int getLineNumber() const { return line_number; }  // ADD GETTER
};

extern ASTNode* root;

// Type helper stubs
void setDeclarationType(ASTNode* node, const std::string &type);
std::string setDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual = 0);
std::string setDirectDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual = 0);
std::string setAbstractDirectDeclaratorType(ASTNode* node, const std::string &type);
std::string setAbstractDeclaratorType(ASTNode* node, const std::string &type);

#endif // AST_H

