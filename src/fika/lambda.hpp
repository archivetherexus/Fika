#pragma once
#ifndef FIKA_LAMBDA_HPP
#define FIKA_LAMBDA_HPP

namespace fika {
    template<typename T> class Lambda;

    template<typename R, typename... A> class Lambda<R(A...)> {
	public:
		template<typename T> Lambda(T t) {
			lambda_container = new LambdaContainerWithT<T>(t);
		}
		template<typename T> Lambda &operator=(T t) {
			lambda_container = new LambdaContainerWithT<T>(t);
			return *this;
		}
		Lambda(const Lambda &other) {
			lambda_container = other.lambda_container->copy();
		}
		R operator()(A... args) const {
			//assert(lambda_container); // TODO: Better error reporting.
			return lambda_container->invoke(args...);
		}
		~Lambda() {
			if (lambda_container) /* TODO: This should normally, not be necessary. */ {
				delete lambda_container;
			}
		}
	private:
		class LambdaContainer {
		public:
			virtual ~LambdaContainer() = default;
			virtual LambdaContainer *copy() = 0;
			virtual R invoke(A... args) = 0;
		};
		template<typename T> class LambdaContainerWithT : public LambdaContainer {
		public:
			LambdaContainerWithT(const T &lambda)
				: lambda(lambda) {
			}
			LambdaContainer *copy() override {
				return new LambdaContainerWithT<T>(lambda);
			} 
			~LambdaContainerWithT() override = default;
			R invoke(A... args) override {
				return lambda(args...);
			}
			T lambda;
		};

		LambdaContainer *lambda_container;
	};
}

#endif