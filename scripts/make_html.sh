#!/bin/bash


dtypes=("uint32" "float32" "uint64" "float64" "int128")
itypes=("uint32" "uint64")

datadir="run_data"
cpu=`grep '^model name\s*:' ${datadir}/cpuinfo | head -1 \
	| awk 'BEGIN {FS=": "} {print $2}'`
cat <<.END
<html>
  <head>
   <style type="text/css">
     body {
         max-width: 60em;
         margin-left: auto;
         margin-right: auto;
     }
   </style>
  </head>
  <body>
    <h1>$cpu</h1>
    <a href="cpuinfo">Full CPU info</a>
    <p>
    <a href="gcc-v">Full GCC info</a>
    <p>
    <pre>
    `cat ${datadir}/free-h`
    </pre>
    <h2>Cache Profile</h2>
    <img src="cacher.svg">
.END

for dt in ${dtypes[@]}; do
  for it in ${itypes[@]}; do
    cat <<.ENDER
    <h2>${dt} data with ${it} indices</h2>
    <table><tr>
      <td>
      <a href="absolute-${dt}-${it}.svg"><img src="absolute-${dt}-${it}.svg" width="400"></a>
      </td>
      <td>
      <a href="relative-${dt}-${it}-rel.svg"><img src="relative-${dt}-${it}-rel.svg"  width="400"></a>
      </td>
    </tr></table>
.ENDER
  done
done

cat <<.END
  </body>
</html>
.END



