package tripexporter;

import java.awt.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

import java.awt.event.*;
import java.io.File;

/**
 * 
 * @author Christian V. (aka MrChrHD/StoKatze/Bunny/King Bunny I)
 * @version  2.0 05/11/2018
 * @since Java 8
 *
 */
public class Window extends JFrame implements ActionListener
{
	//----- Other Windows
	
	/**
	 * Done window
	 */
	Done success = new Done();
	
	/**
	 * About window
	 */
	Info infoWindow = new Info();
	
	/**
	 * How to window
	 */
	HowTo howto = new HowTo();
	
	
	//----- Panels!
	
	/**
	 * Title panel
	 */
	private JPanel p1 = new JPanel();	
	/**
	 * File selection panel
	 */
	private JPanel p2 = new JPanel();
	/**
	 * Lower panel (reset and generate csv button)
	 */
	private JPanel p3 = new JPanel();
	/**
	 * Main Panel
	 */
	private JPanel mainP = new JPanel();
	
	
	//----- TextFields!
	
	/**
	 * Shows selected path
	 */
	private JTextField path = new JTextField();
	
	//----- Buttons!
	
	/**
	 * "Generate" button
	 */
	private JButton generate = new JButton("Export CSV");
	/**
	 * "Reset" button
	 */
	private JButton reset = new JButton("Reset");
	/**
	 * "Open" Button to open file
	 */
	private JButton chooseFile = new JButton("Open...");
	
	//----- Labels!
	
	/**
	 * Title
	 */
	private JLabel title = new JLabel("ETS2/ATS CSV Trip Exporter", SwingConstants.CENTER);
	
	/**
	 * gamesiidirectory label;
	 */
	private JLabel siidir = new JLabel("Open game.sii file (unsure where to find it? Check the How to use section!)");
	
	
	//----- MenuBar & elements!
	
	JMenuBar menuBar = new JMenuBar();
	JButton howTo = new JButton("How to Use");
	JButton info = new JButton("About");
	
	public Window()
	{
		super("ETS2 / ATS CSV Trip Exporter");
		
		generateWindow();
	}

	public void generateWindow()
	{
		//Menu Creation
		menuBar.add(howTo);
		howTo.addActionListener(this);
		menuBar.add(info);
		info.addActionListener(this);
		
		//Title
		p1.add(title);
		p1.add(siidir);
		GridLayout titleLayout = new GridLayout(2,1,0,25);
		p1.setLayout(titleLayout);
		
		//Path Selection Panel
		path.setEditable(false);
		path.setPreferredSize(new Dimension(500,24));
		chooseFile.setSize(new Dimension(80,24));
		chooseFile.addActionListener(this);
		p2.add(path, BorderLayout.CENTER);
		p2.add(chooseFile, BorderLayout.LINE_END);
		
		//Bottom Buttons Panel
		p3.add(generate);
		generate.addActionListener(this);
		generate.setSize(100,24);
		p3.add(reset);
		reset.addActionListener(this);
		GridLayout buttonsLayout = new GridLayout(2,1,25,25);
		p1.setLayout(buttonsLayout);
		
		//Add sub-panels to main panel
		mainP.add(p1);
		mainP.add(p2);
		mainP.add(p3);
		GridLayout finalLayout = new GridLayout(0,1);
		mainP.setLayout(finalLayout);

		//Add main panel to window
		getContentPane().add(mainP);
		
		//Add MenuBar to window 
		this.setJMenuBar(menuBar);
		
		//Set size 
		this.pack();
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//Show window
		this.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent E)
	{
		String command = E.getActionCommand();
		if(command.equals("How to Use"))
		{
			howto.setVisible(true);
		}
		if(command.equals("About"))
		{
			infoWindow.setVisible(true);
		}
		if(command.equals("Open..."))
		{
			//New file chooser
			JFileChooser chooser = new JFileChooser();
			FileNameExtensionFilter SIIfilter = new FileNameExtensionFilter("*.sii Files", "sii", "sii"); //choose only SII filters
			chooser.setFileFilter(SIIfilter);
			chooser.setAcceptAllFileFilterUsed(false); //Remove all files filter
			
			int option = chooser.showOpenDialog(mainP); 
			if (option == JFileChooser.APPROVE_OPTION)
			{
			   File selectedFile = chooser.getSelectedFile(); //Choose file
			   path.setText(selectedFile.getAbsolutePath()); //Get Path
			}
		}
		if(command.equals("Reset"))
		{
			path.setText("");
			generate.setEnabled(true);
		}
		if(command.equals("Export CSV"))
		{
			generate.setEnabled(false);
			if(GenerateCSV.Generate(path.getText()) == true)
			{
				success.setVisible(true);
			}
			else
			{
				success.setVisible(true);
			}
		}
		
	}

}
