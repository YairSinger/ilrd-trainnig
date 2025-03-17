 
 
#ifndef BASE_EX2_HPP    
#define BASE_EX2_HPP  
 class Base
   {
   public:
    Base(int i);
    virtual void foo();
    virtual void bar();
      

  protected:
    virtual ~Base() = 0;

  private:
    int m_i;
    int *m_iptr;
  };

  #endif /* BASE_EX2_HPP */