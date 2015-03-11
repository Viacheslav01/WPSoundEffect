using System;
using System.Threading.Tasks;
using System.Windows;
using Windows.Storage;
using Windows.Storage.Streams;
using Microsoft.Phone.Controls;

namespace SoundEffect
{
	public partial class MainPage : PhoneApplicationPage
	{
		public MainPage()
		{
			InitializeComponent();
		}

		private async void PlaySoundClick(object sender, RoutedEventArgs e)
		{
			var soundEffect = await CreateSoundEffectFromFile("ms-appx:///Assets/sound.wav");
			soundEffect.Play();
		}

		private async Task<XAudio2SoundEffect.SoundEffect> CreateSoundEffectFromFile(string fileUri)
		{
			if (string.IsNullOrWhiteSpace(fileUri))
			{
				return null;
			}

			try
			{
				var file = await StorageFile.GetFileFromApplicationUriAsync(new Uri(fileUri));
				var buffer = await ReadFile(file);

				return new XAudio2SoundEffect.SoundEffect(buffer);
			}
			catch (Exception ex)
			{
				return null;
			}
		}

		private async Task<byte[]> ReadFile(StorageFile file)
		{
			using (var stream = await file.OpenReadAsync())
			using (var reader = new DataReader(stream))
			{
				var buffer = new byte[stream.Size];

				await reader.LoadAsync((uint)stream.Size);
				reader.ReadBytes(buffer);

				return buffer;
			}
		}
	}
}