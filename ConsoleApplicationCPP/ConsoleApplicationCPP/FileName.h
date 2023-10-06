#pragma once

template <typename T>
class shared_ptr {
	T* data;
	int* RefCount;
public:
	shared_ptr(T* ptr) : data(ptr), RefCount(new int()) {}

	shared_ptr(const shared_ptr<T>& other) : data(other.data), RefCount(other.ref_count) {
		(*RefCount)++;
	}

	T* getData() const {
		return data;
	}

	T& operator*() const {
		return *data;
	}

	T* operator->() const {
		return data;
	}

	shared_ptr<T>& operator=(const shared_ptr<T>& other) {
		if (this == &other) {
			return *this;
		}

		(*RefCount)--;
		if (*RefCount == 0) {
			delete data;
			delete RefCount;
		}
		data = other.data;
		RefCount = other.RefCount;
		(*RefCount)++;

		return *this;
	}

	~shared_ptr() {
		(*RefCount)--;
		if (*RefCount == 0) {
			delete data;
			delete RefCount;
		}
	}
};