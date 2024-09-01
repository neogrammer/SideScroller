#ifndef SEQUENCE_H__
#define SEQUENCE_H__
#include <queue>
template <typename T>
class Sequence
{

	std::queue<T> script_sequence;
public:

	std::queue<T>& get()
	{
		return script_sequence;
	}

	void pushScript(T script)
	{
		script_sequence.push(std::move(script));
	}

	void update()
	{
		if (script_sequence.empty())
		{
			script_sequence.front().update();

			if (script_sequence.front().isDone())
			{
				script_sequence.pop();
			}
		}
	}
};

#endif