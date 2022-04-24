let input = ''

process.stdin.on('data', function (data) {
  input += String(data)
})

process.stdin.on('end', function () {
  main()
})

function main () {
  const s = input.split('\n')
  const n = s.length - 1
  const data = s.slice(0, n - 1).map(line => {
    const a = line.split(',')
    a[1] = Number(a[1])
    return a
  })
  const [x, y, z] = s[n - 1].split(',')
  let ds = data.map(x => x[0])
  const ss = data.map(x => x[1])
  const xi = ds.findIndex((a) => a === x)
  ds.splice(xi, 1)
  const yi = ds.findIndex((a) => a === y)
  ds = [...ds.slice(0, yi + 1), x, ...ds.slice(yi + 1)]
  for (let i = 0; i < ds.length; i++) {
    console.log(`${ds[i]},${ss[i]}`)
  }
}

/*
a,1
b,3
c,6
d,8
e,9
f,19
e,a,b

a,1
e,3
b,6
c,8
d,9
f,19
*/
