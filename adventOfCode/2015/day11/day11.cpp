#include <bitset>
#include <cctype>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

class Password {
public:
  Password(std::string s) {
    m_length = s.length();
    m_cond.reset();
    m_value.resize(m_length);

    for (size_t i = 0; i < m_length; ++i) {
      m_value[i] = s[i] - 'a';
    }
  };

  void Advance() {
    m_value[m_length - 1] += 1;
    for (int i = m_length - 1; i > 0; --i) {
      if (m_value[i] > 25) {
        m_value[i] -= 26;
        m_value[i - 1] += 1;
      }
    }
  };

  bool CheckConditions() {
    ThreeInRow() ? m_cond.set(0) : m_cond.reset(0);
    ValidCharacters() ? m_cond.set(1) : m_cond.reset(1);
    TwoInRow() ? m_cond.set(2) : m_cond.reset(2);

    return m_cond.all();
  };

  std::string ToString() {
    std::string res = "";
    for (int i = 0; i < m_length; ++i) {
      res += m_value[i] + 'a';
    }
    return res;
  }

private:
  bool ThreeInRow() {

    for (int i = 0; i < m_length - 3; ++i) {
      if (m_value[i + 1] == m_value[i] + 1 &&
          m_value[i + 2] == m_value[i + 1] + 1)
        return true;
    }

    return false;
  }

  bool ValidCharacters() {
    for (int i = 0; i < m_length; ++i) {
      if (m_value[i] == 'i' || m_value[i] == 'o' || m_value[i] == 'l')
        return false;
    }

    return true;
  }

  bool TwoInRow() {
    for (int i = 0; i < m_length - 3; ++i)
      if (m_value[i + 1] == m_value[i])
        for (int j = i + 2; j < m_length - 1; ++j)
          if (m_value[j] == m_value[j + 1])
            return true;

    return false;
  };

  int m_length;
  std::vector<int> m_value;
  std::bitset<3> m_cond;
};

std::string firstChallenge(std::string s) {
  Password pass(s);

  while (!pass.CheckConditions())
    pass.Advance();

  return pass.ToString();
};

int main() {
  std::string inp = "hepxcrrq";
  std::string s1 = firstChallenge(inp);
  std::cout << s1 << std::endl;
}
