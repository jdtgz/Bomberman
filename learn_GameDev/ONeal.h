#pragma once
#include "Valcom.h"
class ONeal : public Valcom
{
public:
	ONeal(const sf::Vector2i&);
	ONeal(const sf::Vector2i&, const dir&);
	~ONeal();
protected:
	virtual void init(const sf::Vector2i&, const dir&) override;
	virtual double getClippingMargin() const override;
};