using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using XnaSoundEffect.Resources;

namespace XnaSoundEffect
{
	public partial class MainPage
		: PhoneApplicationPage
	{
		public MainPage()
		{
			InitializeComponent();
		}

		private void PlaySoundClick(object sender, RoutedEventArgs e)
		{
			var stream = TitleContainer.OpenStream("Assets/sound.wav");
			var soundEffect = SoundEffect.FromStream(stream);
			var instance = soundEffect.CreateInstance();

			FrameworkDispatcher.Update();

			instance.Play();
		}
	}
}