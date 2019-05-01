package main

import (
  "fmt"
  "os"
  "log"
  "math/rand"
  "time"
  "math"
)


func main() {
  rand.Seed(time.Now().UTC().UnixNano()) // 
  var arq *os.File
  var err error
  arq, err = os.Create("dados")
  if err != nil {
      log.Fatal(err)
  }

  fmt.Println("Digite a quantidade de números a serem gerados: \n")
  var n int
  var escolhe int
  fmt.Scanf("%d", &n)
  for {
    fmt.Println("Digite 1 para valores aleatórios sem ordem.\n")
    fmt.Println("Digite 2 para valores aleatórios em ordem crescente.\n")
    fmt.Println("Digite 3 para valores aleatórios em ordem decrescente.\n")
    fmt.Scanf("%d", &escolhe)
    if escolhe < 4 && escolhe > 0 {
      break // Um número correto foi digitado, logo saímos do loop
    }
  }
  if escolhe == 1 {
	aux := int(math.Floor(float64(n)/(math.Log(math.Log(float64(n))))))
    fmt.Printf("%d", aux)
    for i := 0; i < n; i++ { 
        fmt.Fprintf(arq, "%d\n", rand.Intn(aux))
    } 
  } else if escolhe == 2 {
		var sum int = 0
		aux := int(math.Log2(math.Log2(math.Log2(float64(n)))))
		fmt.Printf("%d", aux)
		if (aux < 2) {
			aux++
		}
		for i := 0; i < n; i++ {
		  sum = sum + rand.Intn(aux)
		  fmt.Fprintf(arq, "%d\n", sum)
		}
  } else if escolhe == 3 {
    //var sum int = 13*n/25
		var sum int = n/2
		aux := int(math.Log2(math.Log2(math.Log2(float64(n)))))
		if (aux < 2) {
			aux++
		}
		fmt.Printf("%d", aux)
		for i := 0; i < n; i++ {
		  sum = sum - rand.Intn(aux)
		  fmt.Fprintf(arq, "%d\n", sum)
		}
  }
  arq.Close()
}
