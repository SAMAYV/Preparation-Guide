#include <iostream>
using namespace std;

namespace first {
	int var = 5;
}
namespace second {
	double var = 3.1416;
}
int main () 
{
	cout << first::var << endl;
	cout << second::var << endl;

	// We could do something likes this, group into blocks
	{
		using namespace first;
		cout << var << endl;
	}
	{
		using namespace second;
		cout << var << endl;
	}
	return 0;
}
/* The functionality of namespaces is especially useful in the case that there is a possibility that a global object or 
function uses the same identifier as another one, causing redefinition errors.
*/