#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class ASTNode {
public:
    std::string name;
    std::string lexeme = "default";
    std::string type = "default";
    std::vector<ASTNode*> children;

    ASTNode* parent;

    bool processed = false;
    // Constructors
    //Node(const std::string &name) : name(name) {}
    ASTNode(const std::string &name_, const std::string &lexeme_ = "")
        : name(name_), lexeme(lexeme_) , parent(nullptr) {}


    // Add child nodes
    void addChild(ASTNode* child);
    void addChild(const std::string &childName);
    void addChild(const std::string &childName, const std::string &childLexeme);

    // Print / debug
    void printTree(int depth = 0, std::string prefix = "");
    void generateDOT(std::ofstream &out, int &nodeId);

    // Type helpers
    void setType(const std::string &type) { this->type = type; }
    std::string getType() const { return type; }
    std::string getLexeme() const { return lexeme; }
};

extern ASTNode* root;

// Type helper stubs
void setDeclarationType(ASTNode* node, const std::string &type);
std::string setDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual = 0);
std::string setDirectDeclaratorType(ASTNode* node, const std::string &type, bool isFunctionDefinition, int isVirtual = 0);
std::string setAbstractDirectDeclaratorType(ASTNode* node, const std::string &type);
std::string setAbstractDeclaratorType(ASTNode* node, const std::string &type);

#endif // AST_H

