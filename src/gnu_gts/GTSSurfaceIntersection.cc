//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//GTSSurfaceIntersection.cc

#include "GTSSurfaceIntersection.h"
#include "GTSSurface.h"

using namespace std;
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

void GTSSurfaceIntersection::borra(void)
  {
    if(!borrar) return;
    if(si) gts_object_destroy(GTS_OBJECT (si));
    si= NULL;
    borrar= false;
  }

GTSSurfaceIntersection::GTSSurfaceIntersection(GtsSurfaceInter *f)
  : si(f), borrar(false) {}

GTSSurfaceIntersection::GTSSurfaceIntersection(GtsSurfaceInterClass *klass,
                                               GTSSurface &s1,
                                               GTSSurface &s2)
  : si(NULL), borrar(true)
  {
    /* build bounding box tree for first surface */
    GNode *tree1 = s1.BBoxTree();

    /* build bounding box tree for second surface */
    GNode *tree2 = s2.BBoxTree();

    si= gts_surface_inter_new( klass,s1.get_ptr(),s2.get_ptr(),
                               tree1,tree2,s1.IsOpen(),s2.IsOpen());
    /* destroy bounding box trees (including bounding boxes) */
    gts_bb_tree_destroy (tree1, TRUE);
    gts_bb_tree_destroy (tree2, TRUE);
  }
GTSSurfaceIntersection::GTSSurfaceIntersection(const GTSSurfaceIntersection &otra)
  : si(otra.si), borrar(false)
  {}
GTSSurfaceIntersection &GTSSurfaceIntersection::operator=(const GTSSurfaceIntersection &otra)
  {
    si= otra.si;
    borrar= false;
    return *this;
  }
GTSSurfaceIntersection::~GTSSurfaceIntersection(void)
  { borra(); }

bool GTSSurfaceIntersection::Check(bool &closed) const
// closed: is set to TRUE if si->edges is a closed curve, FALSE otherwise.
// Returns: TRUE if the curve described by si is an orientable manifold, FALSE otherwise.
  { 
    bool retval;
    gboolean c;
    retval= gts_surface_inter_check(si,&c);
    closed= c;
    return retval;
  }
void GTSSurfaceIntersection::InterBoolean(GTSSurface &surface,GtsBooleanOperation op) const
//Añade a 'surface' la parte de superficie descrita por THIS y op.
//'op' puede tomar los siguientes valores:
// GTS_1_OUT_2 identifies the part of the first surface which lies outside the second surface.
// GTS_1_IN_2 identifies the part of the first surface which lies inside the second surface.
// GTS_2_OUT_1 identifies the part of the second surface which lies outside the first surface.
// GTS_2_IN_1 identifies the part of the second surface which lies inside the first surface.
  { gts_surface_inter_boolean(si,surface.get_ptr(),op); }


GTSSurface GTSSurfaceIntersection::bool_op(const std::string &str_op,GTSSurface &s2) const

  {
    GTSSurface retval;
    if (str_op=="union")
      {
        InterBoolean(retval, GTS_1_OUT_2);
        InterBoolean(retval, GTS_2_OUT_1);
      }
    else 
      if (str_op=="inter")
        {
          InterBoolean(retval, GTS_1_IN_2);
          InterBoolean(retval, GTS_2_IN_1);
        }
      else
        if (str_op=="diff")
          {
            InterBoolean(retval, GTS_1_OUT_2);
            InterBoolean(retval, GTS_2_IN_1);
            gts_surface_foreach_face (si->s2, (GtsFunc) gts_triangle_revert, NULL);
            gts_surface_foreach_face (s2.get_ptr(), (GtsFunc) gts_triangle_revert, NULL);
          }
        else
          {
	    std::cerr << "GTSSurfaceIntersection: la operación: " << str_op
		      << " es desconocida." << std::endl;
          }
    return retval;
  }

static void write_edge (GtsSegment * s, FILE * fp)
  {
    fprintf (fp, "VECT 1 2 0 2 0 %g %g %g %g %g %g\n",
	     GTS_POINT (s->v1)->x,
	     GTS_POINT (s->v1)->y,
             GTS_POINT (s->v1)->z,
	     GTS_POINT (s->v2)->x,
	     GTS_POINT (s->v2)->y,
	     GTS_POINT (s->v2)->z);
  }

void GTSSurfaceIntersection::Write(FILE *fp)
  {
    fprintf(fp,"LIST {\n");
    g_slist_foreach (si->edges, (GFunc) write_edge, fp);
    fprintf(fp,"}\n");
  }


GTSSurface BoolOp(const GTSSurfaceIntersection &si,GTSSurface &s1, GTSSurface &s2,const std::string &str_op,bool check_self_intersection,bool verbose)
  {
    GTSSurface retval;

    /* check that the surfaces are orientable manifolds */
    if (!s1.IsOrientable())
      {
        cerr << "BoolOp: la superficie s1 no es orientable." << endl; 
        return retval;
      }
    if (!s2.IsOrientable())
      {
        cerr << "BoolOp: la superficie s2 no es orientable." << endl; 
        return retval;
      }

    /* check that the surfaces are not self-intersecting */
    if (check_self_intersection)
      {
        if(s1.CheckSelfIntersection(verbose)) return retval;
        if(s2.CheckSelfIntersection(verbose)) return retval;
      }
    
    bool closed;
    g_assert(si.Check(closed));
    if(!closed)
      {
        cerr << "BoolOp: la intersección de s1 y s2 no es una curva cerrada" << endl;
        return retval;
      }
    retval= si.bool_op(str_op,s2);
  
    /* check that the resulting surface is not self-intersecting */
    if(check_self_intersection) retval.CheckSelfIntersection(verbose);

    return retval;
  }
