#include <stdio.h>
#include <Magick++.h>

#include "traffic_automata.h"

using namespace Magick;

int main( int argc, char* argv[] )
{
    srand( (int)time( NULL ) );

    const int width = 512;
    const int height = 512;

    const int frameCount = 128;// 512;
    //const int holdingFrames = 16;

    system( "rd /s /q output" );
    system( "md output" );

    //Image originalImage;
    //originalImage.read( "Animated_lights_on_the_Christmas_tree_part_1-512px.png" );

    //TrafficAutomata tf( originalImage.columns(), originalImage.rows() );
    TrafficAutomata tf( width, height );
    tf.Randomise( 0.35f );
    /*for ( int y = 0; y < height; ++y )
    {
        for ( int x = 0; x < width; ++x )
        {
            TrafficCell* cell = tf.GetCell( x, y );
            Color colour = originalImage.pixelColor( x, y );
            cell->direction = colour.alphaQuantum() != 0 ? UNOCCUPIED : ( rand() % 2 ? VERTICAL : HORIZONTAL );
        }
    }*/

    std::vector<Image> frameList;
    for ( int i = 0; i < frameCount; ++i )
    {
        Image blank_image( Geometry( width, height ), Color() );
        for ( int y = 0; y < height; ++y )
        {
            for ( int x = 0; x < width; ++x )
            {
                TrafficCell* cell = tf.GetCell( x, y );

                Color color( cell->direction != UNOCCUPIED ? ( cell->direction == HORIZONTAL ? "red" : "green" ) : "black" );
                /*Color c;
                if ( cell->direction == UNOCCUPIED )
                {
                    c = Color( "white" );
                }
                else
                {
                    //c = Color( ( (float)cell->originalX / (float)width ) * QuantumRange, ( (float)cell->originalY / (float)height ) * QuantumRange, 0 );
                    c = originalImage.pixelColor( cell->originalX, cell->originalY );
                }*/
                blank_image.pixelColor( x, y, color );
            }
        }

        //if ( i > holdingFrames )
        {
            tf.Multistep( 50 );
        }

        char filename[255];
        sprintf_s( filename, 255, "output/frame%03d.png", i );// frameCount - i );
        //blank_image.magick( "png" );
        blank_image.write( filename );
        //frameList.push_back( blank_image );
        printf( "\rFrame: %03d/%d", i, frameCount );
    }
    //animateImages( frameList.begin(), frameList.end() );
    //frameList.begin()->write( "animation.gif" );
    //blank_image.pixelColor( 8, 8, Color( "red" ) );
    //Container
    //coalesceImages<()
    //Container* ct;

    //writeImages( frameList.begin(), frameList.end(), "foobar.gif" );
    system( "convert -delay 10 -loop 0 output/frame*.png animated.gif" );
    
    return 0;
}