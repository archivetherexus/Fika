#pragma once
#ifndef FIKA_LAMBDA_HPP
#define FIKA_LAMBDA_HPP

namespace fika {
    template <typename T> class Lambda;

    template <typename ReturnValue, typename... Args> class Lambda<ReturnValue(Args...)> {
public:
	template <typename T> Lambda& operator=(T t) {
		lambda_container = new CallableT<T>(t);
		return *this;
	}

	ReturnValue operator()(Args... args) const {
		//assert(lambda_container); // TODO: Better error reporting.
		return lambda_container->Invoke(args...);
	}

    ~Lambda() {
        delete lambda_container;
    }

private:
	class ICallable {
	public:
		virtual ~ICallable() = default;
		virtual ReturnValue Invoke(Args...) = 0;
	};

	template <typename T> class CallableT : public ICallable {
	public:
		CallableT(const T& t)
			: t_(t) {
		}

		~CallableT() override = default;

		ReturnValue Invoke(Args... args) override {
			return t_(args...);
		}

	private:
		T t_;
	};

	ICallable *lambda_container;
};
}

#endif