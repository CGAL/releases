import java.awt.*;
import java.io.*;
import java.awt.event.*;

class Point
{
  public double x=0;
  public double y=0;
  
  public Point()
  {
    x=0;
    y=0;
  }
  public Point(double x, double y)
  {
    this.x = x;
    this.y = y;
  }
  public void print(OutputStream os) throws IOException
  {
    byte[] toPrint=("("+x+","+y+")").getBytes();
    
    os.write(toPrint);
  }
  public double x() { return x; }
  public double y() { return y; }

  public void setX(double x) { this.x = x; }
  public void setY(double y) { this.y = y; }

  public boolean equal(Point p)
  {
    return (x==p.x() && y==p.y());
  }  
  public boolean beforeOrUnder(Point p)
  {
    if (x<p.x() || 
	x==p.x() && y<p.y) return true;
    return false;
  }
}

class Segment
{
  public Point source;
  public Point target;
  public Color color;
  
  public Segment()
  {
  }
  public Segment(Point a, Point b)
  {
    source = a;
    target = b;
    color  = new Color(0,0,0);
  }
  public Segment(Point a, Point b, Color c)
  {
    source = a;
    target = b;
    color  = c;
  }
  public Point source()
  {
    return source;
  }
  public Point target()
  {
    return target;
  }
  public Color color()
  {
    return color;
  }
  public void setSource(Point p)
  {
    source = p;
  }
  public void setTarget(Point p)
  {
    target = p;
  }
  public void setColor(Color c)
  {
    color  = c;
  }
  public void print(OutputStream os) throws IOException
  {
    source.print(os);
    os.write("-".getBytes());
    target.print(os);
  }
  public boolean equal(Segment s)
  {
    return (source==s.source && target==s.target);
  }
}

class Face
{
  public Point[] vertex;
  public int 	 nrVertices;
  public Color   color;
  
  public Face() { }
  public Face(int n, Point[] p, Color c)
  {
    vertex 	= new Point[n];
    nrVertices = n;
    color	= c;
    
    int i;
    for (i=0; i<n; i++) vertex[i] = p[i];
  }

  Point vertex(int i) { return vertex[i]; }
  int size() { return nrVertices; }
  Color color() { return color; }
  
}

class PlanarMap 
{
  public Point[] vertex;
  public Segment[] edge;
  public Face[] face;
  
  public int nrPoints;
  public int nrEdges ;
  public int nrFaces ;
  
  public PlanarMap(){}

  public void ReadPlanarMap(String fileName, boolean readFaces) throws IOException 
  {
    
    // read the data 
    FileReader pmReader = new FileReader(fileName);
    StreamTokenizer sTok = new StreamTokenizer(pmReader);
      
    sTok.nextToken();
    nrPoints = (int)sTok.nval;

    vertex=new Point[nrPoints];

    for (int i = 0; i < nrPoints; i++) {
      sTok.nextToken();
      double x = sTok.nval;
      
      sTok.nextToken();
      double y = sTok.nval;

      vertex[i]=new Point(x,y);
    }
    
    sTok.nextToken();
    nrEdges = (int)sTok.nval;
    
    edge = new Segment[nrEdges];
    for (int i = 0; i < nrEdges; i ++) {
      sTok.nextToken();
      int v1= (int)sTok.nval;
      
      sTok.nextToken();
      int v2= (int)sTok.nval;
      
      sTok.nextToken();
      int c = (int)sTok.nval;
      Color color = new Color(0);
      
      switch(c){
      case 1: color = new Color(255, 0, 0 );
	break;
      case 2: color = new Color(0,0,0);
	break;
      case 3: color = new Color(0, 255, 0);
      }
      edge[i] = new Segment(vertex[v1-1], vertex[v2-1], color);
    }

    if (!readFaces){
      pmReader.close();
      return;
    }
    
    sTok.nextToken();
    nrFaces = (int)sTok.nval;
    face = new Face[nrFaces];
    
    for (int i = 0; i < nrFaces; i ++) {
      sTok.nextToken();
      int e = (int)sTok.nval;
      Point[] p = new Point[e];
      for (int j=0; j<e; j++){
	sTok.nextToken();
	double x=sTok.nval;
	sTok.nextToken();
	double y=sTok.nval;
	p[j] = new Point(x, y);
      }
      sTok.nextToken();
      int c = (int)sTok.nval;
      Color color = new Color(0);
      
      switch(c){
      case 1: color = new Color(255, 0, 0 );
	break;
      case 2: color = new Color(0,0,0);
	break;
      case 3: color = new Color(0, 255, 0);
      }
      face[i] = new Face(e, p, color);
    }
    
    pmReader.close();
    return;
    
  }

  public void print(OutputStream os) throws IOException
  {
    os.write("Vertices:".getBytes());
    for (int i=0; i<nrPoints; i++){
      vertex[i].print(os);
      os.write("\n".getBytes());
    }
    os.write("Edges:".getBytes());
    for (int i=0; i<nrEdges; i++){
      edge[i].print(os);
      os.write("\n".getBytes());
    }
  }    
}

public class ShowPlanarMaps extends Frame 
                            implements ActionListener, 
                                       ItemListener{
  public PlanarMap pm1 = new PlanarMap();
  public PlanarMap pm2 = new PlanarMap();
  public PlanarMap pmOvl = new PlanarMap();
  
  public double dXMin = -3.0;
  public double dXMax = 3.0;
  public double dYMin = -3.0;
  public double dYMax = 3.0;

  public boolean inAnApplet = false;

  public String currentExample = "./1";
  public Choice exampleChoice;
  public CanvasWithTwoMaps figure;
  
  public ShowPlanarMaps()
  {
    readMaps();
    
    exampleChoice = new Choice();
    readAndInitialize(exampleChoice);
    exampleChoice.addItemListener(this);

    Label label = new Label("Select   an   example");

    Button quitButton = new Button("Exit");
    quitButton.setActionCommand("Quit");
    quitButton.addActionListener(this);
    
    Panel upperArea = new Panel();
    upperArea.add(exampleChoice);
    upperArea.add(label);
    upperArea.add(quitButton);
    
    Panel drawingSurface = new Panel();
    setLayout(new BorderLayout());

    drawingSurface.setLayout(new BorderLayout());    
    drawingSurface.add("North",upperArea);
    figure = new CanvasWithTwoMaps();
    drawingSurface.add("Center", figure);
    
    add("Center", drawingSurface);
  }

  public void readMaps()
  {
    try
      {
	pm1.ReadPlanarMap  (currentExample+"/pm-1.in", false);
	pm2.ReadPlanarMap  (currentExample+"/pm-2.in", false);
	pmOvl.ReadPlanarMap(currentExample+"/pm.out", true);
      }
    catch (IOException e) {
            System.err.println("Caught IOException: " +
			       e.getMessage());
    }
    findMinMax();
    return;
  }
  
  public void findMinMax()
  {
    dXMin = pm1.vertex[0].x();
    dXMax = pm1.vertex[0].x();
    dYMin = pm1.vertex[0].y();
    dYMax = pm1.vertex[0].y();
    
    for(int i=1; i<pm1.nrPoints; i++){
      if (pm1.vertex[i].x()<dXMin)
	dXMin = pm1.vertex[i].x();
      else if (pm1.vertex[i].x()>dXMax)
	dXMax = pm1.vertex[i].x();
      if (pm1.vertex[i].y()<dYMin)
	dYMin = pm1.vertex[i].y();
      else if (pm1.vertex[i].y()>dYMax)
	dYMax = pm1.vertex[i].y();
    }
    for(int i=0; i<pm2.nrPoints; i++){
      if (pm2.vertex[i].x()<dXMin)
	dXMin = pm2.vertex[i].x();
      else if (pm2.vertex[i].x()>dXMax)
	dXMax = pm2.vertex[i].x();
      if (pm2.vertex[i].y()<dYMin)
	dYMin = pm2.vertex[i].y();
      else if (pm2.vertex[i].y()>dYMax)
	dYMax = pm2.vertex[i].y();
    }
  }

  public void readAndInitialize(Choice c)
  {
    File thisDirectory = new File(".");
    File exampleDirectory;
    String[] allFiles = thisDirectory.list();
    
    for (int i=0; i<allFiles.length; i++){
      exampleDirectory = new File(allFiles[i]);
      if (exampleDirectory.isDirectory()){
	c.addItem(allFiles[i]);
      }
    }    
  }
  
  public void itemStateChanged(ItemEvent e) {
    currentExample = exampleChoice.getSelectedItem();
    readMaps();
    figure.repaint();
  }

  public void actionPerformed(ActionEvent e) {
    
    String command = e.getActionCommand();
    
    if (command == "Quit") {
      System.exit(0);
    }
  }

  class CanvasWithTwoMaps extends Canvas {
    public double rX = 1;
    public double rY = 1;
    public double shiftX = 3;
    public double shiftY = 3;
    public int actualHeight;
    public int actualWidth;
    
    public void paint(Graphics g) {
      actualWidth  = (getSize().width-6)/2-2;
      actualHeight = getSize().height-6;

      g.drawRect(3, 3, actualWidth, actualHeight );
      g.drawRect(actualWidth+6, 3, actualWidth, actualHeight );

      rX = actualWidth/(dXMax - dXMin);
      rY = actualHeight/(dYMax - dYMin);
      if (rX<rY) {
	rY = rX;
	shiftX = 3;
	shiftY = -3+(actualHeight-rY*(dYMax - dYMin))/2;
      }
      else {
	rX=rY;
	shiftX = 3+(actualWidth-rX*(dXMax - dXMin))/2;
	shiftY = -3;
      }

      drawMap(g, pm1, 0, false);
      drawMap(g, pm2, 0, false);
      drawMap(g, pmOvl, actualWidth+3, true);

    }

    public Dimension getMinimumSize() {
      return new Dimension(700,500);
    }

    public Dimension getPreferredSize() {
      return getMinimumSize();
    }

    public Insets getInsets() {
      return new Insets(30,10,10,10);
    }

    public void drawMap(Graphics g, 
			PlanarMap pm, 
			int offSet, 
			boolean colorFaces)
    {
      if (colorFaces)
	for (int i=0; i<pm.nrFaces; i++){
	  Polygon polygon = new Polygon();
	  for (int j=0; j<pm.face[i].size(); j++){
	    polygon.addPoint(offSet + (int)(shiftX+
					    (pm.face[i].vertex(j).x()-
					     dXMin)*rX),
			     actualHeight-(int)(shiftY+
						(pm.face[i].vertex(j).y()-
						 dYMin)*rY));
	  }

	  int c1=0, 
	    c2=0, 
	    c3=0;
	  
	  if (pm.face[i].color().getRed()==255)
	    c1 = 127;
	  else if (pm.face[i].color().getGreen()==255)
	    c2 = 127;
	  else{
	    c1 = 127;
	    c2 = 127;
	    c3 = 127;
	  }
	  g.setColor(new Color(c1, c2, c3));
	  g.fillPolygon(polygon);
	}

      for (int i=0; i<pm.nrEdges; i++){
	g.setColor( pm.edge[i].color());
	g.drawLine(offSet + (int)(shiftX+(pm.edge[i].source().x()-dXMin)*rX),
	           actualHeight-(int)(shiftY+(pm.edge[i].source().y()-dYMin)*rY),
		   offSet + (int)(shiftX+(pm.edge[i].target().x()-dXMin)*rX),
                   actualHeight-(int)(shiftY+(pm.edge[i].target().y()-dYMin)*rY));
      }   
    }
  }
     
  public Dimension getMinimumSize() {
    return new Dimension(800, 500);
  }

  public Dimension getPreferredSize() {
    return getMinimumSize();
  }

  public boolean handleEvent(Event event) {
    if (event.id == Event.WINDOW_DESTROY) {
      if (inAnApplet) {
	dispose();
      } else {
	System.exit(0);
      }
    }   
    return super.handleEvent(event);
  }
 
  public static void main(String[] args) {
    ShowPlanarMaps windowForMaps = new ShowPlanarMaps();
    windowForMaps.setTitle("Planar Maps");
    windowForMaps.inAnApplet = false;
    
    windowForMaps.pack();
    windowForMaps.show();    
  }
  
}

