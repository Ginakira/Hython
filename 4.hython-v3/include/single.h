/************************************************************
    File Name : single.h
    Author: Ginakira
    Mail: ginakira@outlook.com
    Github: https://github.com/Ginakira
    Created Time: 2020/09/02 09:52:32
************************************************************/

#ifndef _SINGLE_H
#define _SINGLE_H

#include <mutex>

#include "./handle.h"
#include "./parameter.h"
#include "./value.h"

namespace haizei {
class Singleton {
   public:
   protected:
    Singleton() = default;
    static std::mutex m_mutex;
};

class MasterChainSingle : public Singleton {
   public:
    static SIValue run(ASTNode, std::shared_ptr<Parameter> &);

   private:
    static const IHandle *get();
    MasterChainSingle() = delete;
    static const IHandle *SingleInit();
    static const IHandle *object;
};
}  // namespace haizei
#endif