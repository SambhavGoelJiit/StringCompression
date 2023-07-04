#include <bits/stdc++.h>

using namespace std;

struct node
{
  int freq;
  char ch;
  node *left;
  node *right;

  node(int f, char c, node *l = NULL, node *r = NULL)
  {
    freq = f;
    ch = c;
    left = l;
    right = r;
  }
};

struct mycmp
{
  bool operator()(node *l, node *r)
  {
    if (l != NULL && r != NULL)
    {
      return l->freq > r->freq;
    }
    return false;
  }
};

void printhcodes(node *root, string res = "") // res not by reference so no need to pass changes not reflected
{
  if (root == NULL)
  {
    return;
  }
  if (root->ch != '#')
  {
    cout << endl
         << root->ch << " -> " << res;
    return;
  }
  printhcodes(root->left, res + '0');
  printhcodes(root->right, res + '1');
}

void storehcodes(node *root, map<char, string> &codes, string res = "") // res not by reference so no need to pass changes not reflected
{
  if (root == NULL)
  {
    return;
  }
  if (root->ch != '#')
  {
    codes[root->ch] = res;
    return;
  }
  storehcodes(root->left, codes, res + '0');
  storehcodes(root->right, codes, res + '1');
}

void gethcodes(char arr[], int freq[], int n, map<char, string> &codes)
{
  priority_queue<node *, vector<node *>, mycmp> pq;
  for (int i = 0; i < n; i++)
  {
    pq.push(new node(freq[i], arr[i]));
  }
  while (pq.size() > 1)
  {
    node *l = pq.top();
    pq.pop();
    node *r = pq.top();
    pq.pop();
    node *pp = new node(l->freq + r->freq, '#', l, r);
    pq.push(pp);
  }
  node *root = pq.top();
  printhcodes(root);
  storehcodes(root, codes);
}

void decode(string cmp, map<char, string> codes)
{
  string ans = "";
  string temp = "";
  for (int i = 0; i < cmp.size(); i++)
  {
    temp.push_back(cmp[i]);
    for (auto mp = codes.begin(); mp != codes.end(); mp++)
    {
      if (mp->second == temp)
      {
        char c = mp->first;
        ans.push_back(c);
        temp = "";
        break;
      }
    }
  }
  cout << endl
       << "STRING AFTER DECOMPRESSING IT:" << endl
       << ans;
}

string
getcmp(string str)
{
  int cho;
  unordered_map<char, int> m;
  for (int i = 0; i < str.length(); i++)
  {
    m[str[i]]++;
  }

  auto mp = m.begin();
  char arr[m.size()];
  int freq[m.size()];
  for (int i = 0; i < m.size(); i++)
  {
    arr[i] = mp->first;
    freq[i] = mp->second;
    mp++;
  }
  map<char, string> codes;
  gethcodes(arr, freq, m.size(), codes);
  string cmp;
  for (int i = 0; i < str.length(); i++)
  {
    cmp = cmp + codes[str[i]];
  }
  cout << endl
       << "STRING COMPRESSED SUCCESFULLY!!!" << endl;
  cout << endl
       << "ENTER 1 TO PRINT COMPRESSED STRING: " << endl;
  cin >> cho;
  if (cho == 1)
  {
    cout << endl
         << "COMPRESSED STRING IS :" << cmp;
  }

  cout << endl
       << "enter 1 if you Would like to check for losless compression? " << endl;
  cin >> cho;
  if (cho == 1)
  {
    decode(cmp, codes);
  }
  return cmp;
}

int main()
{
  int cho;
  while (1)
  {
    cout << endl
         << "ENTER 1 FOR STATIC INPUT 2 FOR USER INPUT:" << endl;
    cin >> cho;
    if (cho == 1)
    {
      string str;
      str = "acaaacaacaasaaaadaaabbbbbbsbbbsbsbbbbbbcsbbbbsb";
      cout << endl
           << "STRING COMPRESSED IS: " << str;
      string compstr = getcmp(str);
      cout << endl
           << "ENTER 1 TO CHECK FOR EFFECIENCY: " << endl;
      cin >> cho;
      if (cho == 1)
      {
        cout << endl
             << "ORIGNAL SIZE:" << 8 * str.length() << " bits ";
        cout << endl
             << "COMPRESSED SIZE:" << compstr.length() << " bits ";
        int diff = 8 * str.length() - compstr.length();
        cout << endl
             << "MEMORY SAVED:" << diff << " bits ";
        float pt = (float)diff / (8 * str.length());
        pt = pt * 100;
        cout << endl
             << "PERCENTAGE: COMPRESSED:" << pt << " percent ";
      }
    }
    else if (cho == 2)
    {
      string str;
      cout << endl
           << "ENTER STRING TO BE COMPRESSED:" << endl;
      cin >> str;
      string compstr = getcmp(str);
      cout << endl
           << "ENTER 1 TO CHECK FOR EFFECIENCY: " << endl;
      cin >> cho;
      if (cho == 1)
      {
        cout << endl
             << "ORIGNAL SIZE:" << 8 * str.length() << " bits ";
        cout << endl
             << "COMPRESSED SIZE:" << compstr.length() << " bits ";
        int diff = 8 * str.length() - compstr.length();
        cout << endl
             << "MEMORY SAVED:" << diff << " bits ";
        float pt = (float)diff / (8 * str.length());
        pt = pt * 100;
        cout << endl
             << "PERCENTAGE: COMPRESSED:" << pt << " percent ";
      }
    }
    else
    {
      cout << endl
           << "WRONG CHOICE!!";
      cout << endl
           << "DO YOU WANT TO COMPRESS ANOTHER STRING??" << endl;
      cout << endl
           << "1 for yes 2 for no";
      cin >> cho;
      if (cho == 1)
      {
        continue;
      }
      else
      {
        break;
      }
    }
    cout << endl
         << "DO YOU WANT TO COMPRESS ANOTHER STRING??" << endl;
    cout << endl
         << "1 for yes 2 for no";
    cin >> cho;
    if (cho == 1)
    {
      continue;
    }
    else
    {
      break;
    }
  }

  return 0;
}
