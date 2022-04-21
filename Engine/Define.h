#pragma once
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }


#define DECLARE_SINGLE(type)		\
private:							\
	type() {}						\
	~type() {}						\
public:								\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;	}		


#define WINFO  GEngine->GetWinfo()


#define SENTENCE_MAX 80
#define SPEACHSENTENCE_MAX 40
#define NAMELENGTH 20