#pragma once

class Initializable
{
public:

	/// only initialize if necessary
	virtual void ensureInitialized();

	/// rerun the initialization code even if we've already initialized
	virtual void reinitialize();

	bool isInitialized() const;

protected:
	/// provide the ability to initialize
	virtual void init() = 0;

private:
	bool m_isInitialized = false;
}; 