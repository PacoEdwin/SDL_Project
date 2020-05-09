#include "initializable.h"

void Initializable::ensureInitialized()
{
	if (!isInitialized()) 
		this->reinitialize();
}

void Initializable::reinitialize()
{
	this->init();
	m_isInitialized = true;
}

bool Initializable::isInitialized() const
{
	return m_isInitialized;
}