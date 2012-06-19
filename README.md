# The project Detiq-T

The project Detiq-T provides a solid basis for people who are interested
by image processing. It can be used by students, teachers or researcher
working on the topic, but not only. Anyone who wants to implement
processing algorithm can find an interest in this project. Detiq-T is
divided into two parts : ImageIn, the image processing library, and
GenericInterface, which allows users to demonstrate their work easily.


## ImageIn, the image processing library

ImageIn is an image processing library providing several low-level
actions, such as reading/writing in image file (currently supported :
PNG, JPEG and BMP standards), converting from one format to another,
etc. It provides a complete and solid structure capable of handling any
type of image. It is written in plain C++, with a great wish of portability so
it can be used on every popular systems such as Linux, Windows and Mac
OS. Some algorithms are already implemented, but the philosophy of
ImageIn is to be easy to extend and anyone can add his own algorithm to
the library.

The conception of ImageIn makes it very easy to extend. The user can add
his own functions. The algorithms, for example, are all using the same
interface, so they can be used together easily. This way of thinking
helps to build an extensible and generic library.


## GenericInterface, a basis for demonstrative applications

A demonstrative environment is included in Detiq-T, to help users
demonstrate their work. It is called GenericInterface, and it provides a
lot of services, based on ImageIn (such as opening, displaying and
editing image files). Moreover, it gives useful widgets for a better
understanding of image processing, like histograms.

Thanks to Qt, GenericInterface is as portable as ImageIn, and it fits in
you system easily. Its philosophy is the same than the library : we want
you to be able to build an application quickly and effectively, so it is
highly customizable with your own widgets and algorithms.

## Copyright

DETIQ-T is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DETIQ-T is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.