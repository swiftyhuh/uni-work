BEGIN{
  cnt=0
  }

$5 ~ / 914 / {
  cnt++
  print $5
  }
END{
  print cnt
  }
