#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "TronGame.h"

int main(int, char* []) {
	cycle::Minigin engine;
	const TronGame game{};
	engine.SetGame(&game);
	engine.Run();
	return 0;
}
