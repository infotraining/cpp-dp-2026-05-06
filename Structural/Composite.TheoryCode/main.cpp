#include "composite.hpp"

using namespace std;

int main()
{
    // Create a tree structure
    shared_ptr<Composite> root = make_shared<Composite>("root");

    root->add(make_shared<Leaf>("Leaf A"));
    root->add(make_shared<Leaf>("Leaf B"));

    shared_ptr<Composite> comp = make_shared<Composite>("Composite X");
    comp->add(make_shared<Leaf>("Leaf XA"));
    comp->add(make_shared<Leaf>("Leaf XB"));

    root->add(comp);
    root->add(make_shared<Leaf>("Leaf C"));

    // Add and remove a leaf
    shared_ptr<Leaf> leaf = make_shared<Leaf>("Leaf D");
    root->add(leaf);

    // Recursively display tree
    root->display(1);

    std::cout << "\n\n---------------------\n\n";

    root->remove(leaf);

    root->display(1);
}
