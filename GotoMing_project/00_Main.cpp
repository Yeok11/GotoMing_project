#include "Shy_Define.h"
#include "Shy_Core.h"

int main()
{
	if (GM::GetInstance()->Init())
	{
		GM::DestroyInst();
		return 0;
	}

	GM::GetInstance()->Run();
	GM::DestroyInst();
}