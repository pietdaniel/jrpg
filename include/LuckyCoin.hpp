#ifndef LUCKYCOIN_HPP
#define LUCKYCOIN_HPP
#include "IHoldable.hpp"
#include "Global.hpp"
#include <string>


class LuckyCoin : public IHoldable  {
	public:
		LuckyCoin() : IHoldable() {
			name = "Lucky Coin";
			description = "A lucky coin, of little use.";
		}

		~LuckyCoin();

		virtual void action();
		virtual void action(Toon* target);

};
#endif