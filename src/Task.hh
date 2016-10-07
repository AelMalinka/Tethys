/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_TASK_INC
#	define ENTROPY_ASIO_TASK_INC

#	include <functional>
#	include "Exception.hh"

	namespace Entropy
	{
		namespace Asio
		{
			class Task
			{
				public:
					Task();
					Task(const std::function<void()> &);
					Task(const Task &);
					Task(Task &&);
					virtual ~Task();
					virtual void operator () ();
				private:
					std::function<void()> _task;
			};
		}
	}

#endif
