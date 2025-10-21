#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class ASTNode {
public:
    std::string name;
    std::string lexeme;
    std::string type;
    std::vector<ASTNode*> children;
    ASTNode* parent;
    bool processed;  // For semantic analysis
    
    // Constructor
    ASTNode(const std::string& nodeName, const std::string& nodeLexeme = "default")
        : name(nodeName), lexeme(nodeLexeme), type("default"), parent(nullptr), processed(false) {}
    
    // Destructor
    ~ASTNode() {
        for (auto child : children) {
            delete child;
        }
    }
    
    // Add child node
    void addChild(ASTNode* child);
    void addChild(const std::string &childName);
    void addChild(const std::string &childName, const std::string &childLexeme = "default");

    // Set type
    void setType(const std::string& t) { type = t; }
    
    // Print tree
    void printTree(int depth = 0, std::string prefix = "");
    
    // Generate DOT format for Graphviz
    void generateDOT(std::ofstream& out, int& nodeId);
    
    // Helper to check if node has specific name
    bool isName(const std::string& n) const { return name == n; }
    
    // Helper to get child by index safely
    ASTNode* getChild(size_t index) {
        return (index < children.size()) ? children[index] : nullptr;
    }
    
    // Helper to count children
    size_t childCount() const { return children.size(); }
};

// Type helper functions (for compatibility)
void setDeclarationType(ASTNode* node, const std::string& type);
std::string setDeclaratorType(ASTNode* node, const std::string& type, bool = false, int = 0);
std::string setDirectDeclaratorType(ASTNode* node, const std::string& type, bool = false, int = 0);
std::string setAbstractDirectDeclaratorType(ASTNode* node, const std::string& type);
std::string setAbstractDeclaratorType(ASTNode* node, const std::string& type);

#endif // AST_H