#pragma once
#include "Valcom.h"
class ONeal : public Valcom
{
public:
	ONeal(const sf::Vector2i&);
	ONeal(const sf::Vector2i&, const directions&);
	~ONeal();
protected:
	virtual void init(const sf::Vector2i&, const directions&) override;
	virtual double getClippingMargin() const override;
};