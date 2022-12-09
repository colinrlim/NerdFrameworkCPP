#include "Parallel.h"

void Parallel::For(int fromInclusive, int toExclusive, const std::function<void(int)>& body) {
	const int numThreads = std::thread::hardware_concurrency();
	const int chunkSize = (toExclusive - fromInclusive) / numThreads;

	std::vector<std::thread> threads(numThreads);

	for (int i = 0; i < numThreads; i++) {
		const int start = i * chunkSize;
		const int end = (i + 1) == numThreads ? (toExclusive - start) : start + chunkSize;

		threads[i] = std::thread([&body, start, end]()->void {
			for (int i = start; i < end; i++)
				body(i);
		});
	}

	for (int i = 0; i < numThreads; i++)
		threads[i].join();
}

template <typename T>
void Parallel::ForEach(std::vector<T>& source, const std::function<void(T&)>& body) {
	const int numThreads = std::thread::hardware_concurrency();
	const int chunkSize = source.size() / numThreads;

	std::vector<std::thread> threads(numThreads);

	for (int i = 0; i < numThreads; i++) {
		const int start = i * chunkSize;
		const int end = (i + 1) == numThreads ? source.size() : start + chunkSize;

		threads[i] = std::thread([&body](std::vector<T>& source, const int start, const int end)->void {
			for (int i = start; i < end; i++)
				body(source[i]);
		}, source, start, end);
	}

	for (int i = 0; i < numThreads; i++)
		threads[i].join();
}