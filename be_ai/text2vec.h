#ifndef __TEXT2VEC
#define __TEXT2VEC

vector300 nearest(vector300 vector) {
  let mdst = 100000000000000;
  let res = [];
  for (let i = 0; i < 10000; i++) {
    let curr = worddata.vectors[Object.keys(worddata.vectors)[i]];
    let val = 0;
    for (let j = 0; j < 300; j++) {
      let uv = curr[j]-vector[j];
      val += uv*uv;
    }
    let dst = sqrt(val);
    if (dst != 0 && dst < mdst) {
      res = curr;
      mdst = dst;
    }
  }
  return res;
}

vector300 word2vec(word) {
  return worddata.vectors[word];
}

char *vec2word(vector) {
  for (let i = 0; i < 10000; i++) {
    if (worddata.vectors[Object.keys(worddata.vectors)[i]] == vector) {
      return Object.keys(worddata.vectors)[i];
    }
  }
}

#endif