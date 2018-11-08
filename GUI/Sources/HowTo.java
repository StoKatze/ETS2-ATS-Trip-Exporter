package tripexporter;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * 
 * @author Christian V. (aka MrChrHD/StoKatze/Bunny/King Bunny I)
 * @version  2.0 05/11/2018
 * @since Java 8
 *
 */
public class HowTo extends JFrame implements ActionListener
{
	/**
	 * Main panel.
	 */
	private JPanel mainP = new JPanel();
	
	/**
	 * OK button. Will close the window if clicked.
	 */
	private JButton OK = new JButton("OK");
	
	/**
	 * Message.
	 */
	private JLabel message = new JLabel("<html>Game.sii is usually located in C:\\Users\\Your User\\Documents\\Euro Truck simulator 2\\Profiles\\YourProfile\\save\\SaveYouWantToAnalyze<br />" + 
			"You can use Windows explorer to find it. Just open Documents then the Euro Truck Simulator 2 (or American Truck Simulator) folder.<br />" + 
			"Inside it open Profiles folder. The profile's names are written in hexadecimal. If you're not sure you can find hexadecimal to text converters on the internet.<br />" + 
			"Open your profile folder. Inside it open saves folder. You want to analyze the latest save game which is usually \"autosave\" (because the game also saves your game progress when closing ETS2/ATS).<br />" + 
			"Open it and choose game.sii file. Finally click \"Generate CSV\" button. The program will do the rest!<br />" +
			"After it's done, just open Trips.csv. If there is no such file check Log.txt. If you're unsure contact me on steam: mrchrhd.</html>");
	
	/**
	 * Window generation
	 */
	public HowTo()
	{
		super("How to use");
		
		message.setForeground(Color.BLACK);
		mainP.add(message, BorderLayout.CENTER);
		mainP.add(OK, BorderLayout.PAGE_END);
		OK.addActionListener(this);
		mainP.setLayout(new GridLayout(2,1));
		this.getContentPane().add(mainP);
		this.setSize(800, 300);
		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	/**
	 * Checks for ok button clicked.
	 */
	public void actionPerformed(ActionEvent E)
	{
		String clicked = E.getActionCommand();
		if(clicked.equals("OK"))
		{					
			HowTo.super.dispose(); //Closes the window
		}
	}
}
