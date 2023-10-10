Study of the security of an innovative authentication system
----------------------------------------

### Author

- Selim Lakhdar <selim.lakhdar@gmail.com>

## Dockerfile

```sh
$ ./docker.sh
```

You may have to re-launch the docker_entry_point ....

## Usage example

### Python Scripts

#### spatial_px :

Construct new image from the 8 adjacent pixel, for each pixel

```sh
python3 src/spatial_px.py -h
usage: spatial_px.py [-h] [-i INPUT] [-o OUT] [-c CALCULATE] [-s SKIP]

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        input image
  -o OUT, --out OUT     output file
  -c CALCULATE, --calculate CALCULATE
                        caculate : mean [1] | median [2] | standard variation
                        [3]
  -s SKIP, --skip SKIP  skip n pixels (for x&y)

```

#### spatial_square :

Construct new image from pixel blocks (edge*edge) of the image.  
Threshold use ;  
&nbsp;&nbsp; if res > threshold : take white pxl  
&nbsp;&nbsp; if res < threshold : take black pxl

```sh
usage: spatial_square.py [-h] [-i INPUT] [-o OUT] [-e EDGE] [-t THRESHOLD]
                         [-c CALCULATE] [-s SKIP]

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        input image
  -o OUT, --out OUT     output file
  -e EDGE, --edge EDGE  edge size
  -t THRESHOLD, --threshold THRESHOLD
                        threshold for the calculation
  -c CALCULATE, --calculate CALCULATE
                        caculate : mean [1] | median [2] | standard variation
                        [3]
  -s SKIP, --skip SKIP  skip n pixels (for x&y)
```

#### temporal_px :

Construct new image from the 8 adjacent pixel, for each pixel, with n images  
n = [past_img] U [origin_img] U [future_img]
Threshold use ;  
&nbsp;&nbsp; if res > threshold : take white pxl  
&nbsp;&nbsp; if res < threshold : take black pxl

```sh
usage: temporal_px.py [-h] [-o OUTPUT] [-i INPUT [INPUT ...]] [-t THRESHOLD]
                      [-c CALCULATE] [-s SKIP]

optional arguments:
  -h, --help            show this help message and exit
  -o OUTPUT, --output OUTPUT
                        output image
  -i INPUT [INPUT ...], --input INPUT [INPUT ...]
                        input images list
  -t THRESHOLD, --threshold THRESHOLD
                        threshold for the calculation
  -c CALCULATE, --calculate CALCULATE
                        caculate : mean [1] | median [2] | standard variation
                        [3]
  -s SKIP, --skip SKIP  skip n pixels (for x&y)

```

#### temporal_square :

Construct new image from block pixel, with n images  
n = [past_img] U [origin_img] U [future_img]
Threshold use ;  
&nbsp;&nbsp; if res > threshold : take white pxl  
&nbsp;&nbsp; if res < threshold : take black pxl

```sh
usage: temporal_square.py [-h] [-o OUTPUT] [-i INPUT [INPUT ...]]
                          [-c CALCULATE] [-e EDGE] [-t THRESHOLD] [-s SKIP]

optional arguments:
  -h, --help            show this help message and exit
  -o OUTPUT, --output OUTPUT
                        output image
  -i INPUT [INPUT ...], --input INPUT [INPUT ...]
                        input images list
  -c CALCULATE, --calculate CALCULATE
                        caculate : mean [1] | median [2] | standard variation
                        [3]
  -e EDGE, --edge EDGE  edge block length
  -t THRESHOLD, --threshold THRESHOLD
                        threshold for the calculation
  -s SKIP, --skip SKIP  skip n pixels (for x&y)

```

#### tor :

_ToutOuRien_ Mobile Average Filter
Can be used for the 8 adjacent pixls, or for the 2 vertical/horizontal.
Can be used to reach invariance.

```sh
usage: tor.py [-h] [-i INPUT] [-o OUT] [-t TIMES] [-m MODE]

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        input image
  -o OUT, --out OUT     output file
  -t TIMES, --times TIMES
                        nb iteration
  -m MODE, --mode MODE  mode: 0 reach invariance | 1 get_neighbours | 2
                        get_vertical_neighbours | 3 get_horizontal_neighbours
```

#### tor_square :

_ToutOuRien_ Mobile Average Filter
Used for block pixls.

```sh
usage: tor_square.py [-h] [-i INPUT] [-o OUT] [-t TIMES] [-e EDGE]

optional arguments:
  -h, --help            show this help message and exit
  -i INPUT, --input INPUT
                        input image
  -o OUT, --out OUT     output file
  -t TIMES, --times TIMES
                        apply n times
  -e EDGE, --edge EDGE  square edge size

```


### Scripts

Launch scripts with n threads (bash process)

```sh
./launcher.sh
```

